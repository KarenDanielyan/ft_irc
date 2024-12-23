#ifndef _message_
#define _message_



#define MAX_MESSAGE_LENGTH 512

#include <map>
#include <vector>
#include <iostream>

struct IRCMessage
{
	std::map<std::string, std::string> _tags;
	std::string _source;
	std::string _command;
	std::vector<std::string> _parameters;
};



#endif