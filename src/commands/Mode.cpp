#include "../include/Command.hpp"

Mode::Mode(Server* server): Command(server)
{
}

Mode::~Mode()
{
}

void Mode::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
