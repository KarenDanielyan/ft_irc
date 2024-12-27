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
	if (message._parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "PASS"));
		return ;
	}
	if (client->getState() == Client::LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(message._source, \
			client->getNickname()));
		return ;
	}
	if (data.getPassword() != message._parameters[0])
	{
		throw ReplyException(ERR_PASSWDMISMATCH(message._source, \
			client->getNickname()));
		return ;
	}
	client->setState(Client::LOGIN);
}
