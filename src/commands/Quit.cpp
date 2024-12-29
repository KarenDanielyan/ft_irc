/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:21 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/29 18:28:53 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Quit::Quit() {}

Quit::~Quit() {}

void Quit::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	const Connection*	c;

	std::string reason = "";
	if (message.parameters.size() >= 1)
	{
		std::string msg = message.parameters[0];
		for (unsigned long i = 1; i < message.parameters.size(); i++)
			msg += " " + message.parameters[i];
	}
	else
		reason = "quit with no reason";
	c = client->getConnection();
	server->reply(client->getConnection(), (message.source + " Quit :" + reason));
	data.removeClient(client);
	server->closeConnection(c);
}
