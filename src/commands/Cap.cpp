#include "Command.hpp"

Cap::Cap(Server* server): Command(server)
{
}

Cap::~Cap()
{
}

void Cap::implement(IRCClient *IRCClient, std::vector<std::string> arg)
{
	(void)IRCClient;
	(void)arg;
	throw ReplyException(ERR_UNKNOWNCOMMAND("CAP"));
}
