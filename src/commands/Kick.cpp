#include "../include/Command.hpp"

Kick::Kick(Server* server): Command(server)
{
}

Kick::~Kick()
{
}

void Kick::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
