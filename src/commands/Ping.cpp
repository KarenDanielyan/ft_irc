#include "../include/Command.hpp"

Ping::Ping(Server* server): Command(server)
{
}

Ping::~Ping()
{
}

void Ping::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (arg.empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS("PONG"));
		return;
	}
	throw ReplyException(arg[0]); // or somehow to server
}



// do we need ??