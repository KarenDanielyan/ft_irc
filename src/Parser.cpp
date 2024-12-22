#include "../include/Parser.hpp"

CommandType getCommandType(const std::string& command)
{
    if (command == "CAP")       return CMD_CAP;
    if (command == "INVITE")    return CMD_INVITE;
    if (command == "JOIN")      return CMD_JOIN;
    if (command == "KICK")      return CMD_KICK;
    if (command == "MODE")      return CMD_MODE;
    if (command == "NICK")      return CMD_NICK;
    if (command == "NOTICE")    return CMD_NOTICE;
    if (command == "PART")      return CMD_PART;
    if (command == "PASS")      return CMD_PASS;
    if (command == "PING")      return CMD_PING;
    if (command == "PONG")      return CMD_PONG;
    if (command == "PRIVMSG")   return CMD_PRIVMSG;
    if (command == "QUIT")      return CMD_QUIT;
    if (command == "TOPIC")     return CMD_TOPIC;
    if (command == "USERCMD")   return CMD_USERCMD;
    if (command == "WHO")       return CMD_WHO;
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

	// if (_message._command == "MODE")
	// {
	// if (_message._parameters.empty())
	// 	throw std::invalid_argument("Invalid MODE command: Missing target parameter.");

	// std::string target = _message._parameters[0];

	// if (target[0] != '#') {
	// 	if (_message._parameters.size() < 2)
	// 		throw std::invalid_argument("Invalid MODE command: User mode requires a mode string.");

	// 	std::string modestring = _message._parameters[1];

	// 	if (modestring.empty())
	// 		throw std::invalid_argument("Invalid MODE command: Modestring cannot be empty for user modes.");

	// 	for (char c : modestring) {
	// 		if (c != '+' && c != '-' && !isalpha(c))
	// 			throw std::invalid_argument("Invalid MODE command: Invalid character in modestring for user modes.");
	// 	}
	// } 
	// else if (_message._command == "NICK") 
	// {   
	// 	if (_message._parameters.size() != 1)
	// 		throw std::invalid_argument("Invalid NICK command: Requires exactly 1 parameter.");

	// 	std::string nickname = _message._parameters[0];
	// 	if (nickname.length() < 1 || nickname.length() > 9)
	// 		throw std::invalid_argument("Invalid NICK command: Nickname must be between 1 and 9 characters.");
	// 	for (char c : nickname)
	// 	{
	// 		if (!isalnum(c) && c != '-' && c != '_')
	// 			throw std::invalid_argument("Invalid NICK command: Nickname contains invalid characters. Only alphanumeric characters, '-' and '_' are allowed.");
	// 	}
	// }
	// else if (_message._command == "JOIN")
	// {
	// 	if (_message._parameters.size() < 1)
	// 		throw std::invalid_argument("Invalid JOIN command: Requires at least 1 parameter.");

	// 	for (const auto& param : _message._parameters)
	// 	{
	// 		if (param[0] != '#')
	// 			throw std::invalid_argument("Invalid JOIN command: Channel names must start with '#'.");
	// 		if (param.length() < 2 || param.length() > 50)
	// 			throw std::invalid_argument("Invalid JOIN command: Channel name length must be between 2 and 50 characters.");
	// 		for (char c : param.substr(1))
	// 		{
	// 			if (!isalnum(c) && c != '-' && c != '_' && c != '.')
	// 				throw std::invalid_argument("Invalid JOIN command: Channel name contains invalid characters.");
	// 		}
	// 	}
	// }
	// else if (_message._command == "PRIVMSG")
	// {
	// 	if (_message._parameters.size() < 2)
	// 		throw std::invalid_argument("Invalid PRIVMSG command: Requires at least 2 parameters.");

	// 	std::string target = _message._parameters[0];
	// 	if (target[0] == '#') 
	// 	{
	// 		if (target.length() < 2 || target.length() > 50)
	// 			throw std::invalid_argument("Invalid PRIVMSG command: Channel name length must be between 2 and 50 characters.");
	// 	} 
	// 	else 
	// 	{
	// 		if (target.empty() || target.length() > 9) 
	// 			throw std::invalid_argument("Invalid PRIVMSG command: User target must be a non-empty nickname of 1-9 characters.");
	// 		for (char c : target)
	// 		{
	// 			if (!isalnum(c) && c != '-' && c != '_')
	// 				throw std::invalid_argument("Invalid PRIVMSG command: User target contains invalid characters. Only alphanumeric characters, '-' and '_' are allowed.");
	// 		}
	// 	}

	// 	std::string message = _message._parameters[1];
	// 	if (message.empty())
	// 		throw std::invalid_argument("Invalid PRIVMSG command: Message cannot be empty.");
	// 	if (message.length() > 400)
	// 		throw std::invalid_argument("Invalid PRIVMSG command: Message length exceeds the maximum of 400 characters.");
	// }
	// else if (_message._command == "PART")
	// {
	// 	if (_message._parameters.size() < 1)
	// 		throw std::invalid_argument("Invalid PART command: Requires at least 1 parameter.");

	// 	for (const auto& param : _message._parameters)
	// 	{
	// 		if (param[0] != '#')
	// 			throw std::invalid_argument("Invalid PART command: Channel names must start with '#'.");
	// 		if (param.length() < 2 || param.length() > 50)
	// 			throw std::invalid_argument("Invalid PART command: Channel name length must be between 2 and 50 characters.");
	// 		for (char c : param.substr(1))
	// 		{
	// 			if (!isalnum(c) && c != '-' && c != '_' && c != '.')
	// 				throw std::invalid_argument("Invalid PART command: Channel name contains invalid characters.");
	// 		}
	// 	}
	// }
	// else if (_message._command == "PONG")
	// {
	// 	if (_message._parameters.size() != 1)
	// 		throw std::invalid_argument("Invalid PONG command: Requires exactly 1 parameter.");
		
	// 	std::string server = _message._parameters[0];
	// 	if (server.empty() || server.length() > 100)
	// 		throw std::invalid_argument("Invalid PONG command: Server name or identifier must be between 1 and 100 characters.");
	// }
	// else
	// {
	// 	throw std::invalid_argument("Invalid IRC command: Unknown command.");
	// }













// struct IRCMessage {
//     std::map<std::string, std::string> _tags; // Stores message tags
//     std::string _source;                     // Source (prefix)
//     std::string _command;                    // Command name
//     std::vector<std::string> _parameters;    // Command parameters
// };

// // Helper function to split strings based on a delimiter
// std::vector<std::string> splitString(const std::string& str, char delimiter) {
//     std::vector<std::string> tokens;
//     std::stringstream ss(str);
//     std::string token;

//     while (std::getline(ss, token, delimiter)) {
//         tokens.push_back(token);
//     }

//     return tokens;
// }

// // Function to parse a single IRC command line and fill the IRCMessage struct
// bool parseIRCMessage(const std::string& cmd_line, IRCMessage& irc_message) {
//     if (cmd_line.empty()) {
//         return false; // Failure if the command line is empty
//     }

//     std::string remaining = cmd_line;

//     // Step 1: Check for tags (prefix with '@')
//     if (remaining[0] == '@') {
//         size_t space_pos = remaining.find(' ');
//         if (space_pos != std::string::npos) {
//             std::string tag_part = remaining.substr(1, space_pos - 1);
//             remaining.erase(0, space_pos + 1);

//             // Split tags by semicolon and fill _tags
//             auto tags = splitString(tag_part, ';');
//             for (const std::string& tag : tags) {
//                 size_t eq_pos = tag.find('=');
//                 if (eq_pos != std::string::npos) {
//                     std::string key = tag.substr(0, eq_pos);
//                     std::string value = tag.substr(eq_pos + 1);
//                     irc_message._tags[key] = value;
//                 } else {
//                     irc_message._tags[tag] = ""; // Tags without values
//                 }
//             }
//         }
//     }

//     // Step 2: Check for source (prefix with ':')
//     if (remaining[0] == ':') {
//         size_t space_pos = remaining.find(' ');
//         if (space_pos != std::string::npos) {
//             irc_message._source = remaining.substr(1, space_pos - 1);
//             remaining.erase(0, space_pos + 1);
//         }
//     }

//     // Step 3: Extract command
//     size_t space_pos = remaining.find(' ');
//     if (space_pos != std::string::npos) {
//         irc_message._command = remaining.substr(0, space_pos);
//         remaining.erase(0, space_pos + 1);
//     } else {
//         irc_message._command = remaining;
//         return true; // No parameters to process
//     }

//     // Step 4: Extract parameters
//     while (!remaining.empty()) {
//         // Check if a parameter starts with ':', indicating the rest of the line is one parameter
//         if (remaining[0] == ':') {
//             irc_message._parameters.push_back(remaining.substr(1));
//             break;
//         }

//         // Otherwise, extract parameters separated by spaces
//         space_pos = remaining.find(' ');
//         if (space_pos != std::string::npos) {
//             irc_message._parameters.push_back(remaining.substr(0, space_pos));
//             remaining.erase(0, space_pos + 1);
//         } else {
//             irc_message._parameters.push_back(remaining);
//             break;
//         }
//     }

//     return true; // Parsing successful
// }
