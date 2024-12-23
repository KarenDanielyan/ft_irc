#include "../include/Parser.hpp"

CommandType getCommandType(const std::string command)
{
	if (command == "CAP")
		return CMD_CAP;
	else if (command == "INVITE")
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

int IRCParser::parseMessage(const std::string& rawMessage)
{
	if (rawMessage.length() > MAX_MESSAGE_LENGTH)
	{

		return -1;
	}
	if (rawMessage.substr(rawMessage.length() - 2) != "\r\n")
	{

		return -2;
	}

	std::string message = rawMessage;
	message.erase(0, message.find_first_not_of(" \r\n"));
	message.erase(message.find_last_not_of(" \r\n") + 1);

	if (message.empty()) {
		return -1;
	}

	_message = IRCMessage();

	if (!message.empty() && message[0] == '@') {
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos) {
			throw std::invalid_argument("Invalid IRC message: Tags not followed by a space.");
		}
		_message._tags = parseTags(message.substr(1, spacePos - 1));
		message = message.substr(spacePos + 1);
	}

	if (!message.empty() && message[0] == ':') {
		size_t spacePos = message.find(' ');
		if (spacePos == std::string::npos) {
			throw std::invalid_argument("Invalid IRC message: Missing command after source.");
		}
		_message._source = message.substr(1, spacePos - 1);
		message = message.substr(spacePos + 1);
	}

	size_t spacePos = message.find(' ');
	if (spacePos == std::string::npos) {
		_message._command = message;
		_message._parameters.clear();
	} else {
		_message._command = message.substr(0, spacePos);
		_message._parameters = parseParameters(message.substr(spacePos + 1));
	}

   return validateCommand();
}

std::vector<std::string> parseParameters(const std::string& params)
{
	std::vector<std::string> parameters;
	std::istringstream stream(params);
	std::string param;

	while (std::getline(stream, param, ' ')) {
		if (!param.empty()) {
			if (param[0] == ':') {
				parameters.push_back(param.substr(1) + stream.str().substr(stream.tellg()));
				break;
			}
			parameters.push_back(param);
		}
	}
	return parameters;
}

std::map<std::string, std::string> parseTags(const std::string& tags)
{
	std::map<std::string, std::string> tagMap;
	std::istringstream tagStream(tags);
	std::string tag;

	while (std::getline(tagStream, tag, ';')) {
		size_t equalsPos = tag.find('=');
		if (equalsPos != std::string::npos) {
			tagMap[tag.substr(0, equalsPos)] = tag.substr(equalsPos + 1);
		} else {
			tagMap[tag] = "";
		}
	}

	return tagMap;
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

int IRCParser::validateCommand()
{

	CommandType command = getCommandType(_message._command);

	switch(command)
	{
		case CMD_CAP:

		case CMD_INVITE:
			if (_message._tags.empty())
				// ERR_NOSUCHCHANNEL()
			break;
		case CMD_JOIN:
		case CMD_KICK:
		case CMD_MODE:
		case CMD_NICK:
		case CMD_NOTICE:
		case CMD_PART:
		case CMD_PASS:
		case CMD_PING:
		case CMD_PONG:
		case CMD_PRIVMSG:
		case CMD_QUIT:
		case CMD_TOPIC:
		case CMD_USERCMD:
		case CMD_WHO:
		default:
			break;
	}
	return CMD_UNKNOWN;
}


IRCParser::IRCParser()
{

}

IRCParser::~IRCParser()
{
	
}
