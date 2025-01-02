/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:18:44 by kdaniely          #+#    #+#             */
/*   Updated: 2025/01/02 18:37:10 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Mode::Mode() {}

Mode::~Mode() {}

void Mode::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)server;
	if (message.parameters.size() < 2 || message.parameters[0].empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "MODE"));

	std::string target = message.parameters[0];
	std::string mode_str = message.parameters[1];
	std::string mode_arg = message.parameters[2];
	Channel* channel = data.getChannel(target);
	Client *new_op;

	if (!channel)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "MODE"));
	if (!channel->isExist(client))
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	if (!channel->isOperator(client))
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
	int i = -1;

	while (mode_str[++i])
	{
		bool plus = (mode_str[i] == '+');
		i++;
		switch (mode_str[i])
		{
			case 'i':
				channel->setOnlyInvite(plus);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					channel->getName(), (plus ? "+i" : "-i")));
				break;
			case 't':
				new_op = data.findClient(mode_arg);
				if (!new_op)
					throw ReplyException(ERR_NOSUCHNICK(message.source, \
						mode_arg));
				if (!channel->isExist(new_op))
					throw ReplyException(ERR_NOTONCHANNEL(message.source, mode_arg));
				if (plus)
					channel->addTopicOperator(new_op);
				else if (channel->isTopicOperator(new_op))
					channel->removeTopicOperator(new_op);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					channel->getName(), (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel->setPassword(plus ? mode_arg : "");
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					channel->getName(), (plus ? "+k" : "-k")));
				break;
			case 'o':
				new_op = data.findClient(mode_arg);
				if (!new_op)
					throw ReplyException(ERR_NOSUCHNICK(message.source, \
						mode_arg));
				if (!channel->isExist(new_op))
					throw ReplyException(ERR_NOTONCHANNEL(message.source, mode_arg));
				if (plus)
					channel->addOperator(new_op);
				else if (channel->isOperator(new_op))
					channel->removeOperator(new_op);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					channel->getName(), (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel->setLimit(plus ? std::atol(mode_arg.c_str()) : 0);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					channel->getName(), \
					(plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
