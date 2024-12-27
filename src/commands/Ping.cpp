#include "Command.hpp"

Ping::Ping()
{
}

Ping::~Ping()
{
}

void Ping::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	if (message._parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "PING"));
		return;
	}
	std::string msg = "";
	for (unsigned long i = 1; i < message._parameters.size(); i++)
	{
		msg += message._parameters[i];
		msg += " ";
	}
	server->reply(client->getConnection(), RPL_PING(message._source, msg));
}
