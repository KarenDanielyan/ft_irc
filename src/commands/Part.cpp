/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:07 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 11:33:01 by marihovh         ###   ########.fr       */
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

void Part::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PART"));
	std::string name;
	if (message.parameters[0][0] == '#')
		name = message.parameters[0].substr(1);
	else
		name = message.parameters[0];
	Channel *channel = data.getChannel(name);

	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, name));
	if (!client->getChannel() || client->getChannel()->getName() != name)
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	broadcast(server, channel, RPL_PART(message.source, name));
	channel->removeClient(client);
	client->part();
}
