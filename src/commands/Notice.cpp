#include "../include/Command.hpp"

Notice::Notice(Server* server): Command(server)
{
}

Notice::~Notice()
{
}

void Notice::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
