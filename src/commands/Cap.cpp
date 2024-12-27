#include "Command.hpp"

Cap::Cap() {}

Cap::~Cap() {}

void Cap::implement(Client *client, const ITransport* server, DAL & data, \
			IRCMessage message)
{
	(void)client;
	(void)server;
	(void)data;
	(void)message;
	throw ReplyException(ERR_UNKNOWNCOMMAND(message._source, "CAP"));
}
