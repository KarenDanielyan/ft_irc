#include "../include/Command.hpp"

Notice::Notice(Server* server): Command(server)
{
}

Notice::~Notice()
{
}

void Notice::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
