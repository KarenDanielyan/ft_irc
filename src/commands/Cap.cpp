#include "../include/Command.hpp"

Cap::Cap(Server* server): Command(server)
{
}

Cap::~Cap()
{
}

void Cap::implement(Client *client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
}
