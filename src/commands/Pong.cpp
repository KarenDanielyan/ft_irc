#include "../include/Command.hpp"

Pong::Pong(Server* server): Command(server)
{
}

Pong::~Pong()
{
}

void Pong::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
