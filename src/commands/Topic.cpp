/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:24 by marihovh          #+#    #+#             */
/*   Updated: 2025/01/02 19:48:54 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Topic::Topic() {}

Topic::~Topic() {}

void Topic::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	std::string	name;
	Channel*	channel;

	if (message.parameters.size() < 1)
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "TOPIC"));
	name = message.parameters[0];
	channel = data.getChannel(name);
	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "TOPIC"));
	if (!channel->isExist(client))
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	if (message.parameters.size() == 2)
	{
		if (!channel->isAdmin(client) || !channel->isOperator(client) || !channel->isTopicOperator(client))
			throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
				client->getNickname()));
		std::string topic = message.parameters[1];
		for (size_t i = 2; i < message.parameters.size(); i++)
			topic += " " + message.parameters[i];
		channel->setTopic(topic);
		return ;
	}
	if (channel->getTopic().empty())
		server->reply(client->getConnection(), RPL_NOTOPIC(message.source, name));
	else
		server->reply(client->getConnection(), RPL_TOPIC(message.source, \
			name, channel->getTopic()));
}
