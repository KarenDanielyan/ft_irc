/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:10:12 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:10:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Cap::Cap() {}

Cap::~Cap() {}

void Cap::implement(Client *client, ITransport* server, DAL & data, \
			IRCMessage message)
{
	(void)client;
	(void)server;
	(void)data;
	(void)message;
	throw ReplyException(ERR_UNKNOWNCOMMAND(message.source, "CAP"));
}
