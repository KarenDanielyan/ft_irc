/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:05:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/30 13:43:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "defines.hpp"
#include <sstream>

std::vector<IRCMessage> \
	Parser::parseMessage(std::string& rawMessage, Connection *from)
{
	std::vector<IRCMessage>	_messages;
	static std::string		buffer;
	std::string				message;
	size_t					pos;
	size_t					to_erase;

	while(true)
	{
		to_erase = 2;
		pos = rawMessage.find(CRLF);
		if (pos == std::string::npos)
		{
			pos = rawMessage.find("\n");
			if (pos == std::string::npos)
			{
				buffer.append(rawMessage);
				break ;
			}
			to_erase --;
		}
		message = buffer + rawMessage.substr(0, pos);
		buffer.erase();
		rawMessage = rawMessage.erase(0, pos + to_erase);
		if (message.size() > MAX_MESSAGE_LENGTH)
			_server->reply(from, ERR_INPUTTOOLONG(from->getHostname()));
		else if (message.empty())
			continue ;
		else
			_messages.push_back(_fillIRCMessage(message, from));
	}
	return (_messages);
}

IRCMessage	Parser::_fillIRCMessage(const std::string& line, Connection* from)
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
	if (message.source.empty())
		message.source = from->getHostname();
	// message.source = 
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
