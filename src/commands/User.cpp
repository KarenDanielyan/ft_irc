#include "../include/Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{
}

void User::implement(IRCClient* client, std::vector<std::string> arg)
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
	clinet->setUsername(arg[0]);
	client->setRealName(arg[3]);
	client->SendMessage(client, RPL_WELCOME(application->getName(), client->getUsername()));
}
