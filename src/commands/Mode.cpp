#include "../include/Command.hpp"

Mode::Mode(Server* server): Command(server)
{
}

Mode::~Mode()
{
}

void Mode::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
