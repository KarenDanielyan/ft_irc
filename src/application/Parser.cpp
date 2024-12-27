#include "Parser.hpp"

CommandType Parser::getCommandType(const std::string command)
{
	if (command == "INVITE")
		return CMD_INVITE;
	else if (command == "JOIN")
		return CMD_JOIN;
	else if (command == "KICK")
		return CMD_KICK;
	else if (command == "MODE")
		return CMD_MODE;
	else if (command == "NICK")
		return CMD_NICK;
	else if (command == "NOTICE")
		return CMD_NOTICE;
	else if (command == "PART")
		return CMD_PART;
	else if (command == "PASS")
		return CMD_PASS;
	else if (command == "PING")
		return CMD_PING;
	else if (command == "PONG")
		return CMD_PONG;
	else if (command == "PRIVMSG")
		return CMD_PRIVMSG;
	else if (command == "QUIT")
		return CMD_QUIT;
	else if (command == "TOPIC")
		return CMD_TOPIC;
	else if (command == "USERCMD")
		return CMD_USERCMD;
	else if (command == "WHO")
		return CMD_WHO;
	else
		return CMD_UNKNOWN;
}

int Parser::parseMessage(const std::string& rawMessage)
{
	if (rawMessage.length() == 0 )
		return IGNOR_MESSAGE;
	else if ( rawMessage.length() > MAX_MESSAGE_LENGTH)
		return MESSAGE_TO_LONG;
	else if (rawMessage.substr(rawMessage.length() - 2) != "\r\n")
		return IGNOR_MESSAGE;

	std::string message = rawMessage;
	message.erase(0, message.find_first_not_of(" \r\n"));
	message.erase(message.find_last_not_of(" \r\n") + 1);

	_message = IRCMessage();

	if (!message.empty() && message[0] == ':')
	{
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos)
			return 
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

const IRCMessage& Parser::getMessage() const
{
	return _message;
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

std::string Parser::decodeEscaped(const std::string& rawValue)
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


Parser::Parser() : _message()
{
	// need to intilize client to
}

Parser::~Parser()
{
	
}
