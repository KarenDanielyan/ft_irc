#include "Command.hpp"

Pong::Pong()
{
}

Pong::~Pong()
{
}

void Pong::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	if (message.parameters.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PONG"));
	std::string msg = "";
	for (unsigned long i = 1; i < message.parameters.size(); i++)
	{
		msg += message.parameters[i];
		msg += " ";
	}
	server->reply(client->getConnection(), RPL_PING(message.source, msg));
}
