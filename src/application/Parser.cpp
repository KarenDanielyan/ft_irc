/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:12:27 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:12:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

int Parser::parseMessage(const std::string& rawMessage)
{
	if (rawMessage.length() == 0)
		return IGNOR_MESSAGE;

	else if (rawMessage.length() > MAX_MESSAGE_LENGTH)
		throw ERR_INPUTTOOLONG();

	else if (rawMessage.substr(rawMessage.length() - 2) != "\r\n")
		return IGNOR_MESSAGE;

	std::string message = rawMessage.substr(0, rawMessage.length() - 2);

	if (!message.empty() && message[0] == ':')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			return IGNOR_MESSAGE;
		_message._source = message.substr(1, spacePos - 1);
		message = message.substr(spacePos + 1);
	}

	size_t spacePos = message.find(' ');
	if (spacePos == std::string::npos)
	{
		_message._command = message;
		_message._parameters.clear();
	}
	else
	{
		_message._command = message.substr(0, spacePos);
		_message._parameters = parseParameters(message.substr(spacePos + 1));
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

// std::string Parser::decodeEscaped(const std::string& rawValue)
// {
// 	std::string decoded;
// 	for (size_t i = 0; i < rawValue.size(); ++i)
// 	{
// 		if (rawValue[i] == '\\' && i + 1 < rawValue.size()) 
// 		{
// 			switch (rawValue[i + 1])
// 			{
// 				case ':':
// 					decoded += ':';
// 					break;
// 				case 's':
// 					decoded += ' ';
// 					break;
// 				case '\\':
// 					decoded += '\\';
// 					break;
// 				default:
// 					decoded += rawValue[i + 1];
// 					break;
// 			}
// 			++i;
// 		}
// 		else
// 			decoded += rawValue[i];
// 	}
// 	return decoded;
// }


Parser::Parser() : _message()
{
}

Parser::~Parser()
{
	
}
