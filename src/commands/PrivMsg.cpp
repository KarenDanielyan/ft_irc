/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:18 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:19 by marihovh         ###   ########.fr       */
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

void PrivMsg::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 2 || message.parameters[0].empty() || \
		message.parameters[1].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, \
			client->getNickname() + "PRIVMSG"));
	}
	std::string target = message.parameters[0];
	std::string msg = "";
	for (unsigned long i = 1; i < message.parameters.size(); i++)
	{
		msg += message.parameters[i];
		msg += " ";
	}
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = data.getChannel(name);
		if (!channel)
			throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "PRIVMSG"));
		if (!channel->isExist(client))
			throw ReplyException(ERR_CANNOTSENDTOCHAN(message.source, \
				channel->getName()));
		broadcast(server, channel, msg);
		return ;
	}
	Client *dest = data.findClient(target);
	if (!dest)
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			client->getNickname()));
	server->reply(dest->getConnection(), (message.source + " " + msg));
}
