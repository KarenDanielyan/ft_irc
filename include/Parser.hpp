#ifndef _parser_
#define _parser_

# define Cap 1
# define Who 2
# define Pass 3
# define Join 4
# define Kick 5
# define Mode 6
# define Quit 7
# define Nick 8
# define Pong 9
# define Ping 10
# define Part 11
# define Topic 12
# define Notice 13
# define Invite 14
# define PrivMsg 15
# define UserCmd 16

#include "Command_Data.hpp"

#define val "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"


class IRCParser
{
	private:
		IRCMessage _message;

		std::map<std::string, std::string> parseTags(const std::string& rawTags);
		std::vector<std::string> parseParameters(const std::string& rawParams);
		std::string decodeEscaped(const std::string& rawValue);

	public:
		IRCParser() = default;
		~IRCParser() = default;

		void parseMessage(const std::string& rawMessage);
		const IRCMessage& getMessage() const;

		void processCommand();
};

#endif