#include "../include/Command.hpp"

Part::Part(Server* server): Command(server)
{
}

Part::~Part()
{
}

void Part::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
