/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:38:58 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 18:32:36 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Notice::Notice() {}

Notice::~Notice() {}

void Notice::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 2 || message.parameters[0].empty() || \
			message.parameters[1].empty())
		return;
	std::string target = message.parameters[0];
	std::string msg = message.parameters[1];
	for (unsigned long i = 2; i < message.parameters.size(); i++)
		msg += " " + message.parameters[i];
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = data.getChannel(name);
		if (!channel)
			return ;
		if (!channel->isExist(client))
			return ;
		broadcast(server, channel, message.source + msg);
		return ;
	}	
	Client *dest = data.findClient(target);
	if (!dest)
		return;
	server->reply(client->getConnection(), (message.source + msg));
}
