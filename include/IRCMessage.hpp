#ifndef _message_
#define _message_


# include "defines.hpp"
# include <map>
# include <vector>
# include <iostream>

struct IRCMessage
{
	std::map<std::string, std::string> _tags;
	std::string _source;
	std::string _command;
	std::vector<std::string> _parameters;
	IRCMessage() : _tags(), _source(""), _command(""), _parameters() {}
};



#endif
