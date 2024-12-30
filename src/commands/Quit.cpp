/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:21 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 10:20:06 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Quit::Quit() {}

Quit::~Quit() {}

void Quit::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	const Connection*	c;
	std::string			reason = "";
	std::string			chan_name;
	if (message.parameters.size() >= 1)
	{
		for (size_t i = 0; i < message.parameters.size(); i++)
			reason += " " + message.parameters[i];
	}
	c = client->getConnection();
	server->reply(client->getConnection(), RPL_QUIT(message.source, reason));
	client->setState(Client::DISCONNECTED);
	
	if (!client->getChannel())
	{
		data.removeClient(client);
		server->closeConnection(c);
		return ;
	}
	chan_name = client->getChannel()->getName();
	Channel *it = data.getChannel(chan_name);
	broadcast(server, it, RPL_QUIT(message.source, reason));
	client->part();
	it->removeClient(client);
}
