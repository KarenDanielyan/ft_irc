/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:12 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/29 06:07:38 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Ping::Ping()
{
}

Ping::~Ping()
{
}

void Ping::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PING"));
	std::string msg = message.parameters[0];
	for (unsigned long i = 1; i < message.parameters.size(); i++)
	{
		msg += " ";
		msg += message.parameters[i];
	}
	server->reply(client->getConnection(), RPL_PONG(message.source, msg));
}
