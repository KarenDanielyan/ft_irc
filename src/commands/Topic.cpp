/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:24 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:25 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
// done done
Topic::Topic() {}

Topic::~Topic() {}

void Topic::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 1)
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "TOPIC"));
	std::string name = message.parameters[0].substr(1);
	Channel* channel = data.getChannel(name);
	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "TOPIC"));
	if (!channel->isExist(client))
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	if (!channel->isOperator(client))
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
	if (message.parameters.size() == 2)
	{
		std::string topic = "";
		for (size_t i = 1; i < message.parameters.size(); i++)
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
