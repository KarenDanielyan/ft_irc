#include "../include/Command.hpp"

PrivMsg::PrivMsg(Server* server): Command(server)
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
