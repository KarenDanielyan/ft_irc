#include "Command.hpp"

Ping::Ping(Server* server): Command(server)
{
}

Ping::~Ping()
{
}

void Pingimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS("PING"));
		return;
	}
	std::string message = "";
	for (unsigned long i = 1; i < arg.size(); i++)
	{
		message += arg[i];
		message += " ";
	}
	sendMessage(client, RPL_PING(message));
}