#include "../include/Command.hpp"

Who::Who(Server* server): Command(server)
{
}

Who::~Who()
{
}

void Who::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	// if (arg.empty())
	// {
	// 	//print for who -------- only the IRCClient
	// }
	// std::string mask = arg[0];
	// Channel *channel = _server.channels.find(mask);
	// if (channel)
	// {
	// 	// print channels IRCClients
	// }

	// if (getIRCClient(mask))
	// {
	// 	//reply-> nickname
	// }
}
