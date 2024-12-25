#include "Command.hpp"

Cap::Cap(): Command()
{
}

Cap::~Cap()
{
}

void Cap::implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	(void)Client;
	(void)arg;
	throw ReplyException(ERR_UNKNOWNCOMMAND("CAP"));
}
