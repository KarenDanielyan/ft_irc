/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:59:52 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 18:17:49 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "defines.hpp"

Join::Join() {}

Join::~Join() {}

void Join::validate(Client *client, IRCMessage& message)
{
	(void)client;
	std::string channel = message.parameters[0];
	if ( channel[0] != '#' || channel[0] != '&')
		throw ReplyException(ERR_BADCHANMASK(channel));
}


void Join::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "JOIN"));
	validate(client, message);
	std::string name = message.parameters[0].substr(1);
	std::string pass = message.parameters.size() > 1 ? message.parameters[1] : "";
	std::string topic = "I exist because you wanted to.";
	Channel *channel = data.getChannel(name);
	//if the client is on the channel
	if (!channel)
	{
		data.addChannel(name, topic, pass, client);
		Channel* new_channel = data.getChannel(name);
		new_channel->addClient(client);
		// new_channel->setAdmin(client);
		return ;
	}
	if (channel->isInviteOnly() && !channel->isInvited(client))
		throw ReplyException(ERR_INVITEONLYCHAN(message.source, name));
	if (channel->getLimit() >= channel->getClientCount())
		throw ReplyException(ERR_CHANNELISFULL(message.source, name));
	if (channel->getPassword() != pass)
		throw ReplyException(ERR_BADCHANNELKEY(message.source, name));
	if (channel->isExist(client))
		throw ReplyException(ERR_USERONCHANNEL(message.source, \
			client->getNickname()));
	if (client->getChannel())
	{
		broadcast(server, client->getChannel(), message.source + \
			client->getNickname() + " leaves the " + channel->getName() + \
			" channel because of joining another");
		channel->removeClient(client);
		client->part();
	}
	channel->addClient(client);
	client->join(channel);
	server->reply(client->getConnection(), message.source + " " \
		+ client->getNickname() + " Joined " + \
		channel->getName() + " channel");
	//print about channel
	std::vector<Client *> clients = channel->getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); \
			it != clients.end(); ++it)
	{
		server->reply(client->getConnection(), RPL_NAMREPLY(message.source, \
			channel->getName(), \
			(*it)->getNickname()));
	}
	server->reply(client->getConnection(), RPL_ENDOFNAMES(message.source, \
		channel->getName()));

	if (channel->getTopic() != "")
		server->reply(client->getConnection(), message.source + \
			" Topic of channel: " + channel->getTopic());
}
