/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:10:59 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 02:04:11 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "defines.hpp"

Nick::Nick() {}

Nick::~Nick() {}

void Nick::validate(Client *client,  IRCMessage& message)
{
	std::string	nickname = message.parameters[0];
	const std::string disallowedChars = " ,*?!@";
	const std::string disallowedStartChars = "$:";
	const std::string channelPrefixes = "#&+!";

	(void)client;
	if (nickname.find_first_of(disallowedChars) != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(message.source, nickname));
	if (disallowedStartChars.find(nickname[0]) != std::string::npos \
			|| channelPrefixes.find(nickname[0]) != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(message.source, nickname));

	if (nickname.find('.') != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(message.source, nickname));

	for (size_t i = 0; i < nickname.length(); ++i)
	{
		if (!isalnum(nickname[i]) &&
			nickname[i] != '[' && nickname[i] != ']' &&
			nickname[i] != '{' && nickname[i] != '}' &&
			nickname[i] != '\\' && nickname[i] != '|')
			throw ReplyException(ERR_ERRONEUSNICKNAME(message.source, nickname));
	}
}


void Nick::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (client->getState() == Client::CONNECT)
	{
		server->reply(client->getConnection(), \
				ERR_UNKNOWNERROR(client->getSource(), "NICK", INFO_REGISTER));
		return ;
	}
	validate(client, message);
	if (message.parameters.empty() || message.parameters[0].empty())
		throw ReplyException(ERR_NONICKNAMEGIVEN(message.source));

	std::string nickname = message.parameters[0];
	Client *new_client = data.findClient(nickname);
	
	if (new_client && new_client != client)
		throw ReplyException(ERR_NICKNAMEINUSE(message.source, nickname));
	client->setNickname(nickname);
}
