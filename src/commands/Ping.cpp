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
}



// do we need ??