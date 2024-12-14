#include "../include/Command.hpp"

Nick::Nick(Server* server): Command(server)
{
}

Nick::~Nick()
{
}

void Nick::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
