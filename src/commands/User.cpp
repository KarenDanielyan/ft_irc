#include "../include/Command.hpp"
//done
User::User(Server* server): Command(server)
{
}

User::~User()
{
}

void User::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	// if (is registred)
	// {
	// 	reply->ERR_ALREADYREGISTERED
	// }

	// if (arg.size() < 4)
	// {
	// 	reply->ERR_NEEDMOREPARAMS
	// }
	// clinet->setUsername(arg[0]);
	// IRCClient->setRealName(arg[3]);
}
