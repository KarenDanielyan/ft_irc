#include "../include/Command.hpp"

Topic::Topic(Server* server): Command(server)
{
}

Topic::~Topic()
{
}

void Topic::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
