/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:44:08 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 18:44:10 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

User::User() {}

User::~User() {}

void	User::validate(Client *client, IRCMessage& message)
{
	std::string username = message.parameters[0];
	std::string realname = message.parameters[3];
	std::string param2 = message.parameters[1];
	std::string param3 = message.parameters[2];

	(void)client;
	if (param2 != "0" || param3 != "*")
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "USER"));
	if (username.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "USER"));
	while (!username.empty() && username[0] == ' ')
		username.erase(0, 1);

	if (!realname.empty() && realname[0] == ':')
		realname.erase(0, 1);
}


void User::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	if (message.parameters.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "USER"));
		return ;
	}
	if (client->getState() == Client::LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(message.source, \
			client->getUsername()));
		return ;
	}
	client->setUsername(message.parameters[0]);
	client->setRealname(message.parameters[3]);
	server->reply(client->getConnection(), \
		RPL_WELCOME(message.source, client->getUsername()));
}
