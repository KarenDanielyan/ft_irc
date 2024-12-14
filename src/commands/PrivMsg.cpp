#include "../include/Command.hpp"

PrivMsg::PrivMsg(Server* server): Command(server)
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
