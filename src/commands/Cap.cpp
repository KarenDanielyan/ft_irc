#include "Command.hpp"

Cap::Cap(Server* server): Command(server)
{
}

Cap::~Cap()
{
}

void Cap::implement(Client *Client, std::vector<std::string> arg)
{
	(void)Client;
	(void)arg;
	throw ReplyException(ERR_UNKNOWNCOMMAND("CAP"));
}
