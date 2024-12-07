#include "../include/Command.hpp"

UserCmd::UserCmd(Server* server): Command(server)
{
}

UserCmd::~UserCmd()
{
}

void UserCmd::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
}
