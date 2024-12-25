#include "Command.hpp"

Quit::Quit(Server* server): Command(server)
{
}

Quit::~Quit()
{
}

void Quitimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	std::string reason;
	if (arg[0][0] == ':')
		reason = arg[0].substr(1);
	else
		reason = "quit with no reason";
	SendMessage(client, ":" + reason);
}
