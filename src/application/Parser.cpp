/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:05:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 22:52:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "defines.hpp"
#include <sstream>


/* TODO: Add \r\n as a define callse CRCN */
std::vector<IRCMessage> Parser::parseMessage(std::string& rawMessage, Connection *from)
{
	std::vector<IRCMessage>	_messages;
	std::string				buffer;
	size_t					pos;

	while(true)
	{
		pos = rawMessage.find(CRNL);
		if (pos == std::string::npos)
			break ;
		buffer = rawMessage.substr(0, pos);
		rawMessage = rawMessage.erase(0, pos + 2);
		if (buffer.size() > MAX_MESSAGE_LENGTH)
			_server->reply(from, ERR_INPUTTOOLONG(from->getHostname()));
		else if (buffer.empty())
			continue ;
		else
			_messages.push_back(_fillIRCMessage(buffer));
	}
	return (_messages);
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
		else if (message.command.empty() && (i == 0 || i == 1))
			message.command = arg;
		else
			message.parameters.push_back(arg);
	}
	if (!message.parameters.empty() && (message.parameters.back())[0] == ':')
		message.parameters.back().erase(0, 1);
	return (message);
}

void	Parser::prettyPrint(std::vector<IRCMessage> const & messages)
{
	for (size_t i = 0; i < messages.size(); i ++)
	{
		std::cout << i << ": ";
		std::cout << "Source: " << messages[i].source << std::endl;
		std::cout << "Command: " << messages[i].command << std::endl;
		std::cout << "Argumets: ";
		for (std::vector<std::string>::const_iterator it = \
					messages[i].parameters.begin(); \
					it != messages[i].parameters.end(); it++)
		{
			std::cout << *it << " -> ";
		}
	  std::cout << std::endl << "|" << std::endl;
	}
}

Parser::Parser(ITransport* server) : _server(server) {}

Parser::~Parser() {}
