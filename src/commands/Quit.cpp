/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:21 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:22 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Quit::Quit()
{
}

Quit::~Quit()
{
}

void Quit::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	std::string reason;
	if (message.parameters[0][0] == ':')
		reason = message.parameters[0].substr(1);
	else
		reason = "quit with no reason";
	server->reply(client->getConnection(), (message.source + " Quit :" + reason));
	close(client->getConnection()->getFd());
}
