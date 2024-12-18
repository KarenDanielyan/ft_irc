#include "../include/Command.hpp"

Part::Part(Server* server): Command(server)
{
}

Part::~Part()
{
}

void Part::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
