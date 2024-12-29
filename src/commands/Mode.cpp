/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariam <mariam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:18:44 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 20:37:17 by mariam           ###   ########.fr       */
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

	std::string target = message.parameters[0].substr(1);
	std::string mode_str = message.parameters[1];
	std::string mode_arg = message.parameters[2];
	Channel* channel = data.getChannel(target);

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
					client->getNickname(), \
					channel->getName(), (plus ? "+i" : "-i")));
				break;
			case 't':
				channel->setTopic(plus ? mode_arg : "");
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel->setPassword(plus ? mode_arg : "");
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+k" : "-k")));
				break;
			case 'o':
				if (target != client->getNickname())
					throw ReplyException(ERR_USERSDONTMATCH(message.source));
				if (plus)
					channel->addOperator(client);
				else
					channel->removeOperator(client);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel->setLimit(plus ? std::atol(mode_arg.c_str()) : 0);
				broadcast(server, channel, RPL_CHANNELMODEIS(message.source, \
					client->getNickname(), channel->getName(), \
					(plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
