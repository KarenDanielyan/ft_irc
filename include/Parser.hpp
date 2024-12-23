#ifndef _parser_
#define _parser_


#include "IRCMessage.hpp"
#include <sstream>
#define val "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"


enum CommandType
{
	CMD_CAP,
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


class IRCParser
{
	private:
		IRCMessage _message;

		std::map<std::string, std::string> parseTags(const std::string& rawTags);
		std::vector<std::string> parseParameters(const std::string& rawParams);
		std::string decodeEscaped(const std::string& rawValue);

	public:
		IRCParser();
		~IRCParser();

		int parseMessage(const std::string& rawMessage);
		const IRCMessage& getMessage() const;
		int validateCommand();
		void processCommand() const;
};

#endif