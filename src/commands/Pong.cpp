/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:15 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/29 18:30:06 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Pong::Pong()
{
}

Pong::~Pong()
{
}

void Pong::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PONG"));
	std::string msg = message.parameters[0];
	for (unsigned long i = 1; i < message.parameters.size(); i++)
		msg += " " + message.parameters[i];
	server->reply(client->getConnection(), RPL_PING(message.source, msg));
}
