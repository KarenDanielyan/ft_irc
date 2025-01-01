/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:59:52 by kdaniely          #+#    #+#             */
/*   Updated: 2025/01/02 00:21:51 by marihovh         ###   ########.fr       */
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
	if ( channel[0] != '#' && channel[0] != '&')
		throw ReplyException(ERR_BADCHANMASK(channel));
}


void Join::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	std::string name = message.parameters[0];
	std::string pass = message.parameters.size() > 1 ? message.parameters[1] : "";
	std::string topic = "";
	Channel *channel = data.getChannel(name);

	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "JOIN"));
	if (client->getChannel())
		throw ReplyException(ERR_TOOMANYCHANNELS(message.source, \
			client->getChannel()->getName()));
	validate(client, message);
	if (!channel)
	{
		data.addChannel(name, topic, pass, client);
		channel = data.getChannel(name);
		channel->addOperator(client);
		channel->setOnlyInvite(false);
	}
	else
	{
		if (channel->isInviteOnly() && !channel->isInvited(client))
			throw ReplyException(ERR_INVITEONLYCHAN(message.source, name));
		if (channel->getLimit() >= channel->getClientCount())
			throw ReplyException(ERR_CHANNELISFULL(message.source, name));
		if (channel->getPassword() != pass)
			throw ReplyException(ERR_BADCHANNELKEY(message.source, name));
		if (channel->isExist(client))
			throw ReplyException(ERR_USERONCHANNEL(message.source, \
				client->getNickname(), channel->getName()));
	}
	channel->addClient(client);
	client->join(channel);
	server->reply(client->getConnection(), RPL_JOIN(client->getNickname(), \
		channel->getName()));
	if (channel->isOperator(client)) {
		server->reply(client->getConnection(), RPL_USERMODE(client->getNickname(), \
			channel->getName(), client->getNickname()));
	}
	std::vector<Client *> clients = channel->getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); \
			it != clients.end(); ++it)
	{
		if (channel->isOperator(*it))
		{
			server->reply(client->getConnection(), RPL_NAMREPLY(client->getNickname(), \
				channel->getName(), "@", (*it)->getNickname()));
		}
		else
		{
			server->reply(client->getConnection(), RPL_NAMREPLY(client->getNickname(), \
				channel->getName(), "", (*it)->getNickname()));
		}
	}
	server->reply(client->getConnection(), RPL_ENDOFNAMES(client->getNickname(), \
		channel->getName()));
	broadcast(server, channel, RPL_JOIN(client->getNickname(), channel->getName()));
	if (!channel->getTopic().empty()) {
		server->reply(client->getConnection(), \
				RPL_TOPIC(message.source, \
				channel->getName(), \
				channel->getTopic())
		);
	}
}
