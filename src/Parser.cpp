#include "IRCParser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

void IRCParser::parseMessage(const std::string& rawMessage)
{
	_message = IRCMessage();
	std::istringstream stream(rawMessage);
	std::string token;

	std::string message = rawMessage;
	message.erase(0, message.find_first_not_of(" \r\n"));
	message.erase(message.find_last_not_of(" \r\n") + 1);

	if (message.empty())
		throw std::invalid_argument("Invalid IRC message: Empty message.");

	if (!message.empty() && message[0] == '@')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			throw std::invalid_argument("Invalid IRC message: Tags not followed by a space.");
		std::string tags = message.substr(1, spacePos - 1);
		_message.tags = parseTags(tags);
		message = message.substr(spacePos + 1);
	}

	if (!message.empty() && message[0] == ':')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			throw std::invalid_argument("Invalid IRC message: Missing command after source.");
		_message.source = message.substr(1, spacePos - 1);
		message = message.substr(spacePos + 1);
	}

	std::transform(message.begin(), message.end(), message.begin(), ::toupper);
	size_t spacePos = message.find(' ');
	if (spacePos == std::string::npos)
	{
		_message.command = message;
		_message.parameters.clear();
	}
	else
	{
		_message.command = message.substr(0, spacePos);
		std::string params = message.substr(spacePos + 1);
		_message.parameters = parseParameters(params);
	}

	validateCommand();
	if (rawMessage.length() > MAX_MESSAGE_LENGTH)
		throw std::invalid_argument("Invalid IRC message: Message exceeds 512 characters.");
}

const IRCMessage& IRCParser::getMessage() const
{
	return _message;
}

std::map<std::string, std::string> IRCParser::parseTags(const std::string& rawTags)
{
	std::map<std::string, std::string> tags;
	std::istringstream stream(rawTags);
	std::string tag;

	while (std::getline(stream, tag, ';'))
	{
		size_t eqPos = tag.find('=');
		if (eqPos != std::string::npos)
		{
			std::string key = tag.substr(0, eqPos);
			std::string value = decodeEscaped(tag.substr(eqPos + 1));
			tags[key] = value;
		} 
		else
			tags[tag] = "";
	}
	return tags;
}

std::vector<std::string> IRCParser::parseParameters(const std::string& rawParams)
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

std::string IRCParser::decodeEscaped(const std::string& rawValue)
{
	std::string decoded;
	for (size_t i = 0; i < rawValue.size(); ++i)
	{
		if (rawValue[i] == '\\' && i + 1 < rawValue.size()) 
		{
			switch (rawValue[i + 1])
			{
				case ':':
					decoded += ':';
					break;
				case 's':
					decoded += ' ';
					break;
				case '\\':
					decoded += '\\';
					break;
				default:
					decoded += rawValue[i + 1];
					break;
			}
			++i;
		}
		else
			decoded += rawValue[i];
	}
	return decoded;
}

void IRCParser::validateCommand()
{
	if (_message.command == "NICK")
	{	
		if (_message.parameters.size() != 1)
			throw std::invalid_argument("Invalid NICK command: Requires exactly 1 parameter.");
	}
	else if (_message.command == "JOIN")
	{
		if (_message.parameters.size() < 1)
			throw std::invalid_argument("Invalid JOIN command: Requires at least 1 parameter.");
	}
	else if (_message.command == "PRIVMSG")
	{
		if (_message.parameters.size() < 2)
			throw std::invalid_argument("Invalid PRIVMSG command: Requires at least 2 parameters.");
	}
	else if (_message.command == "PART")
	{
		if (_message.parameters.size() < 1)
			throw std::invalid_argument("Invalid PART command: Requires at least 1 parameter.");
	}
	else if (_message.command == "PONG")
	{
		if (_message.parameters.size() != 1)
			throw std::invalid_argument("Invalid PONG command: Requires exactly 1 parameter.");
	}
}
