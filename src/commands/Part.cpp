/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:07 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:08 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

//<channel>{,<channel>} [<reason>]
Part::Part()
{
}

Part::~Part()
{
}

void Part::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PART"));

	std::string name = message.parameters[0].substr(1);
	Channel *channel = data.getChannel(name);

	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, name));
	if (!client->getChannel() || client->getChannel()->getName() != name)
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	channel->removeClient(client);
	client->part();
	broadcast(server, channel, message.source + \
		client->getNickname() + " PART " + channel->getName());
}
