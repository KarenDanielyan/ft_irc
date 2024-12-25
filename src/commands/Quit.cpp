#include "Command.hpp"

Quit::Quit(Server* server): Command(server)
{
}

Quit::~Quit()
{
}

void Quit::implement(Client* client, std::vector<std::string> arg)
{
	std::string reason;
	if (arg[0][0] == ':')
		reason = arg[0].substr(1);
	else
		reason = "quit with no reason";
	SendMessage(client, ":" + reason);
}
