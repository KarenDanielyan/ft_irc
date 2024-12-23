#include "Command.hpp"

Ping::Ping(Server* server): Command(server)
{
}

Ping::~Ping()
{
}

void Ping::implement(IRCClient* client, std::vector<std::string> arg)
{
	if (arg.empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS("PING"));
		return;
	}
	std::string message = "";
	for (unsigned long i = 1; i < arg.size(); i++)
	{
		message += arg[i];
		message += " ";
	}
	throw ReplyException(RPL_PING(message));
}