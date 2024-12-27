#include "Command.hpp"

Quit::Quit()
{
}

Quit::~Quit()
{
}

void Quit::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)data;
	std::string reason;
	if (message._parameters[0][0] == ':')
		reason = message._parameters[0].substr(1);
	else
		reason = "quit with no reason";
	server->reply(client->getConnection(), (message._source + ":" + reason));
}
