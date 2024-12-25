#include "Command.hpp"

Cap::Cap(): Command()
{
}

Cap::~Cap()
{
}

void Cap::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	(void)client;
	(void)server;
	(void)data;
	(void)message;
	throw ReplyException(ERR_UNKNOWNCOMMAND("CAP"));
}
