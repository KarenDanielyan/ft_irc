/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:05:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 19:13:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

int Parser::parseMessage(const std::string& rawMessage)
{
	if (rawMessage.length() == 0)
		return IGNOR_MESSAGE;

	else if (rawMessage.length() > MAX_MESSAGE_LENGTH)
		throw ReplyException(ERR_INPUTTOOLONG());

	else if (rawMessage.substr(rawMessage.length() - 2) != "\r\n")
		return IGNOR_MESSAGE;

	std::string message = rawMessage.substr(0, rawMessage.length() - 2);

	if (!message.empty() && message[0] == ':')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			return IGNOR_MESSAGE;
		_message.source = message.substr(1, spacePos - 1);
		message = message.substr(spacePos + 1);
	}

	size_t spacePos = message.find(' ');
	if (spacePos == std::string::npos)
	{
		_message.command = message;
		_message.parameters.clear();
	}
	else
	{
		_message.command = message.substr(0, spacePos);
		_message.parameters = parseParameters(message.substr(spacePos + 1));
	}

	return VALID_MESSAGE;
}

const IRCMessage& Parser::getMessage()
{
	return _message;
}


void		Parser::setMessage(const IRCMessage& message)
{
	this->_message = message;
}


std::vector<std::string> Parser::parseParameters(const std::string& rawParams)
{
	std::vector<std::string> parameters;
	std::istringstream stream(rawParams);
	std::string param;

	while (std::getline(stream, param, ' '))
	{
		if (param[0] == ':')
		{
			std::string trailing;
			std::getline(stream, trailing);
			param = param.substr(1) + trailing;
			parameters.push_back(param);
			break;
		}
		parameters.push_back(param);
	}
	return parameters;
}

Parser::Parser() : _message() {}

Parser::~Parser() {}
