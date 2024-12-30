/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:18 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 11:50:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

//done done
//<target>{,<target>} <text to be sent>

PrivMsg::PrivMsg()
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 2 || message.parameters[0].empty() || \
		message.parameters[1].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, \
			client->getNickname() + "PRIVMSG"));
	}
	std::string target = message.parameters[0];
	std::string msg = message.parameters[1];
	for (unsigned long i = 2; i < message.parameters.size(); i++)
		msg += " " + message.parameters[i];
	if (target[0] == '#')
	{
		std::string name = target;
		Channel* channel = data.getChannel(name);
		if (!channel)
			throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "PRIVMSG"));
		if (!channel->isExist(client))
			throw ReplyException(ERR_CANNOTSENDTOCHAN(message.source, \
				channel->getName()));
		broadcast(server, channel, RPL_MSG(message.source, "PRIVMSG", \
			channel->getName(), msg));
		return ;
	}
	Client *dest = data.findClient(target);
	if (!dest)
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			client->getNickname()));
	server->reply(dest->getConnection(), RPL_MSG(message.source, "PRIVMSG", \
		dest->getNickname(), msg));
}
