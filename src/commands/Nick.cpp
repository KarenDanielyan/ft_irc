#include "Command.hpp"
//done
Nick::Nick()
{
}

Nick::~Nick()
{
}

void Nick::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	(void)server;
	if (message._parameters.empty() || message._parameters[0].empty())
	{
		throw ReplyException(ERR_NONICKNAMEGIVEN(message._source, "NICK"));
		return ;
	}
	std::string nickname = message._parameters[0];

	Client *new_client = data->getClient(nickname);
	if (new_client && new_client != client)
	{
		throw ReplyException(ERR_NICKNAMEINUSE(message._source, nickname));
		return;
	}
	client->setNickname(nickname);
}
