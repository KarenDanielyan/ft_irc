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
}


// do we need??