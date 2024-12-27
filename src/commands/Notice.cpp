/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:38:58 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 21:40:23 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Notice::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message._parameters.size() < 2 || message._parameters[0].empty() || \
			message._parameters[1].empty())
		return;
	std::string target = message._parameters[0];
	std::string msg = "";
	for (unsigned long i = 1; i < message._parameters.size(); i++)
	{
		msg += message._parameters[i];
		msg += " ";
	}
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = data.getChannel(name);
		if (!channel)
			return ;
		if (!channel->isExist(client))
			return ;
		broadcast(server, channel, message._source + msg);
		return ;
	}	
	Client *dest = data.findClient(target);
	if (!dest)
		return;
	server->reply(client->getConnection(), (message._source + msg));
}
