#include "../include/Command.hpp"

Pass::Pass(Server* server): Command(server)
{
}

Pass::~Pass()
{
}

void Pass::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}

