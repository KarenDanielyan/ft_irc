#include "../include/Command.hpp"

Join::Join(Server* server): Command(server)
{
}

Join::~Join()
{
}

void Join::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
