/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:10:46 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:10:47 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
//done
Kick::Kick()
{
}

Kick::~Kick()
{
}
//<channel> <user> *( "," <user> ) [<comment>]
void Kick::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)server;
	if (message.parameters.size() < 2)
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "KICK"));

	std::string name = message.parameters[0].substr(1);
	std::string target = message.parameters[1];
	std::string msg = "Reason: ";
	Channel* channel = data.getChannel(name);

	for (unsigned long i = 2; ++i <= message.parameters.size(); i++)
		msg += message.parameters[i];
	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "KICK"));
	if (!channel->isOperator(client))
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
	Client *dest = data.findClient(target);
	if (!dest)
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			client->getNickname()));
	if (client->getChannel()->getName() != name)
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	if (dest->getChannel()->getName() != name)
		throw ReplyException(ERR_USERNOTINCHANNEL(message.source, \
			dest->getNickname()));
	broadcast(server, channel, message.source + " from "+ channel->getName() \
		+ " removed " + dest->getNickname() + " " + msg);
	dest->part();
	channel->removeClient(dest);
}
