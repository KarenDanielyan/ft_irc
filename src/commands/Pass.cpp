/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:10 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 01:43:08 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
//done
Pass::Pass()
{
}

Pass::~Pass()
{
}

void Pass::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)server;
	(void)client;
	(void)data;
	(void)message;
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PASS"));
	if (client->getState() == Client::LIVE)
		throw ReplyException(ERR_ALREADYREGISTERED(message.source));
	if (data.getPassword() != message.parameters[0])
		throw ReplyException(ERR_PASSWDMISMATCH(message.source));
	client->setState(Client::LOGIN);
}
