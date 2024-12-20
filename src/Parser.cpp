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
		_message._tags = parseTags(tags);
		message = message.substr(spacePos + 1);
	}

	if (!message.empty() && message[0] == ':')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			throw std::invalid_argument("Invalid IRC message: Missing command after source.");
		_message._source = message.substr(1, spacePos - 1);
		message = message.substr(spacePos + 1);
	}

	std::transform(message.begin(), message.end(), message.begin(), ::toupper);
	size_t spacePos = message.find(' ');
	if (spacePos == std::string::npos)
	{
		_message._command = message;
		_message._parameters.clear();
	}
	else
	{
		_message._command = message.substr(0, spacePos);
		std::string params = message.substr(spacePos + 1);
		_message._parameters = parseParameters(params);
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
	if (_message._command == "MODE")
	{
	if (_message._parameters.empty())
		throw std::invalid_argument("Invalid MODE command: Missing target parameter.");

	std::string target = _message._parameters[0];

	if (target[0] != '#') {
		if (_message._parameters.size() < 2)
			throw std::invalid_argument("Invalid MODE command: User mode requires a mode string.");

		std::string modestring = _message._parameters[1];

		if (modestring.empty())
			throw std::invalid_argument("Invalid MODE command: Modestring cannot be empty for user modes.");

		for (char c : modestring) {
			if (c != '+' && c != '-' && !isalpha(c))
				throw std::invalid_argument("Invalid MODE command: Invalid character in modestring for user modes.");
		}
	} 
	else if (_message._command == "NICK") 
	{   
		if (_message._parameters.size() != 1)
			throw std::invalid_argument("Invalid NICK command: Requires exactly 1 parameter.");

		std::string nickname = _message._parameters[0];
		if (nickname.length() < 1 || nickname.length() > 9)
			throw std::invalid_argument("Invalid NICK command: Nickname must be between 1 and 9 characters.");
		for (char c : nickname)
		{
			if (!isalnum(c) && c != '-' && c != '_')
				throw std::invalid_argument("Invalid NICK command: Nickname contains invalid characters. Only alphanumeric characters, '-' and '_' are allowed.");
		}
	}
	else if (_message._command == "JOIN")
	{
		if (_message._parameters.size() < 1)
			throw std::invalid_argument("Invalid JOIN command: Requires at least 1 parameter.");

		for (const auto& param : _message._parameters)
		{
			if (param[0] != '#')
				throw std::invalid_argument("Invalid JOIN command: Channel names must start with '#'.");
			if (param.length() < 2 || param.length() > 50)
				throw std::invalid_argument("Invalid JOIN command: Channel name length must be between 2 and 50 characters.");
			for (char c : param.substr(1))
			{
				if (!isalnum(c) && c != '-' && c != '_' && c != '.')
					throw std::invalid_argument("Invalid JOIN command: Channel name contains invalid characters.");
			}
		}
	}
	else if (_message._command == "PRIVMSG")
	{
		if (_message._parameters.size() < 2)
			throw std::invalid_argument("Invalid PRIVMSG command: Requires at least 2 parameters.");

		std::string target = _message._parameters[0];
		if (target[0] == '#') 
		{
			if (target.length() < 2 || target.length() > 50)
				throw std::invalid_argument("Invalid PRIVMSG command: Channel name length must be between 2 and 50 characters.");
		} 
		else 
		{
			if (target.empty() || target.length() > 9) 
				throw std::invalid_argument("Invalid PRIVMSG command: User target must be a non-empty nickname of 1-9 characters.");
			for (char c : target)
			{
				if (!isalnum(c) && c != '-' && c != '_')
					throw std::invalid_argument("Invalid PRIVMSG command: User target contains invalid characters. Only alphanumeric characters, '-' and '_' are allowed.");
			}
		}

		std::string message = _message._parameters[1];
		if (message.empty())
			throw std::invalid_argument("Invalid PRIVMSG command: Message cannot be empty.");
		if (message.length() > 400)
			throw std::invalid_argument("Invalid PRIVMSG command: Message length exceeds the maximum of 400 characters.");
	}
	else if (_message._command == "PART")
	{
		if (_message._parameters.size() < 1)
			throw std::invalid_argument("Invalid PART command: Requires at least 1 parameter.");

		for (const auto& param : _message._parameters)
		{
			if (param[0] != '#')
				throw std::invalid_argument("Invalid PART command: Channel names must start with '#'.");
			if (param.length() < 2 || param.length() > 50)
				throw std::invalid_argument("Invalid PART command: Channel name length must be between 2 and 50 characters.");
			for (char c : param.substr(1))
			{
				if (!isalnum(c) && c != '-' && c != '_' && c != '.')
					throw std::invalid_argument("Invalid PART command: Channel name contains invalid characters.");
			}
		}
	}
	else if (_message._command == "PONG")
	{
		if (_message._parameters.size() != 1)
			throw std::invalid_argument("Invalid PONG command: Requires exactly 1 parameter.");
		
		std::string server = _message._parameters[0];
		if (server.empty() || server.length() > 100)
			throw std::invalid_argument("Invalid PONG command: Server name or identifier must be between 1 and 100 characters.");
	}
	else
	{
		throw std::invalid_argument("Invalid IRC command: Unknown command.");
	}
}
}
