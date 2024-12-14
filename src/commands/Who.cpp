#include "../include/Command.hpp"

Who::Who(Server* server): Command(server)
{
}

Who::~Who()
{
}

void Who::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
