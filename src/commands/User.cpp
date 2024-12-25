#include "Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{
}

void Userimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
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
