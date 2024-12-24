#ifndef _parser_
#define _parser_


#include "IRCMessage.hpp"
#include "Server.hpp"
#include <sstream>
#define val "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

enum CommandType
{
	CMD_INVITE,
	CMD_JOIN,
	CMD_KICK,
	CMD_MODE,
	CMD_NICK,
	CMD_NOTICE,
	CMD_PART,
	CMD_PASS,
	CMD_PING,
	CMD_PONG,
	CMD_PRIVMSG,
	CMD_QUIT,
	CMD_TOPIC,
	CMD_USERCMD,
	CMD_WHO,
	CMD_UNKNOWN
};

#define VALID_MESSAGE 1
#define IGNOR_MESSAGE 417
#define UNKOWN_CMD 0
class IRCParser
{
	private:
		IRCMessage	_message;
	public:
		IRCParser();
		~IRCParser();
	public:
		CommandType					getCommandType(const std::string command);
		std::vector<std::string>	parseParameters(const std::string& rawParams);
		std::string 				decodeEscaped(const std::string& rawValue);
		int 						parseMessage(const std::string& rawMessage);
		const IRCMessage& 			getMessage() const;
		// void 						processCommand() const;
};

#endif