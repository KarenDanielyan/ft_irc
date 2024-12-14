#include "../include/Command.hpp"

Ping::Ping(Server* server): Command(server)
{
}

Ping::~Ping()
{
}

void Ping::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
