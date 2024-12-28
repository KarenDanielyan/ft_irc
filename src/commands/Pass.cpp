#include "Command.hpp"
//done
Pass::Pass()
{
}

Pass::~Pass()
{
}

void Pass::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)server;
	(void)client;
	(void)data;
	(void)message;
	if (message.parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PASS"));
		return ;
	}
	if (client->getState() == Client::LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(message.source, \
			client->getNickname()));
		return ;
	}
	if (data.getPassword() != message.parameters[0])
	{
		throw ReplyException(ERR_PASSWDMISMATCH(message.source, \
			client->getNickname()));
		return ;
	}
	client->setState(Client::LOGIN);
}
