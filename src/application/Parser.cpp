/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:05:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 21:38:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "defines.hpp"
#include <sstream>


/* TODO: Add \r\n as a define callse CRCN */
int Parser::parseMessage(std::string& rawMessage, Connection *from)
{
	std::string	buffer;
	size_t		pos;
	while(true)
	{
		pos = rawMessage.find_first_of("\r\n");
		if (pos == std::string::npos)
			return (IGNOR_MESSAGE);
		buffer = rawMessage.substr(0, pos);
		rawMessage = rawMessage.erase(0, pos + 2);
		if (buffer.size() > MAX_MESSAGE_LENGTH)
			_server->reply(from, ERR_INPUTTOOLONG(from->getHostname()));
		else if (buffer.empty())
			continue ;
		else
			_messages.push_back(_fillIRCMessage(buffer));
	}
}

IRCMessage	Parser::_fillIRCMessage(const std::string& line)
{
	IRCMessage	message;

	std::vector<std::string> arguments;
	std::string arg;
	std::stringstream stream(line);
	for(int i = 0; std::getline(stream, arg, ' '); i++)
	{
		if (arg[0] == ':' && i == 0)
			message.source = arg.substr(1, (arg.length() - 1));
		else if (i == 0 || i == 1)
			message.command = arg;
		else
			message.parameters.push_back(arg);
	}
	if ((message.parameters.back())[0] == ':')
		message.parameters.back().erase(0, 1);
	return (message);
}

std::vector<IRCMessage> const & Parser::getMessages() const
{
	return _messages;
}

Parser::Parser(ITransport* server) : _messages(), _server(server) {}

Parser::~Parser() {}
