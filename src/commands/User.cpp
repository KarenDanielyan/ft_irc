#include "Command.hpp"
//done done
User::User()
{
}

User::~User()
{
}

void User::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	(void)data;
	if (message._parameters.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return ;
	}
	// if (client->getState() == LIVE)
	// {
	// 	throw ReplyException(ERR_ALREADYREGISTERED(client->getUsername()));
	// 	return ;
	// }
	client->setUsername(message._parameters[0]);
	client->setRealname(message._parameters[3]);
	server->reply(client->getConnection(), RPL_WELCOME(client->getUsername()));
}
