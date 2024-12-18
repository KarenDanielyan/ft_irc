#include "../include/Command.hpp"

Topic::Topic(Server* server): Command(server)
{
}

Topic::~Topic()
{
}

void Topic::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
