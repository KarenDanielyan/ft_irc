#include "Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{
}

void User::implement(Client* client, std::vector<std::string> arg)
{
	if (arg.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return ;
	}
	if (client->getState() == LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(client->getUsername()));
		return ;
	}
	client->setUsername(arg[0]);
	client->setRealname(arg[3]);
	SendMessage(client, RPL_WELCOME(client->getUsername()));
}
