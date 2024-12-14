#include "../include/Command.hpp"

Kick::Kick(Server* server): Command(server)
{
}

Kick::~Kick()
{
}

void Kick::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
