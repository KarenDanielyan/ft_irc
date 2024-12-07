#include "../include/Command.hpp"

Quit::Quit(Server* server): Command(server)
{
}

Quit::~Quit()
{
}

void Quit::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
