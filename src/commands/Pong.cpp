#include "Command.hpp"

Pong::Pong(Server* server): Command(server)
{
}

Pong::~Pong()
{
}

void Pong::implement(IRCClient* client, std::vector<std::string> arg)
{
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("PONG"));
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