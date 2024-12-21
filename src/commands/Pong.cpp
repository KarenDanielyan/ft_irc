#include "../include/Command.hpp"

Pong::Pong(Server* server): Command(server)
{
}

Pong::~Pong()
{
}

void Pong::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (arg.empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS("PONG"));
		return;
	}
	throw ReplyException(arg[0]); // or somehow to server
}