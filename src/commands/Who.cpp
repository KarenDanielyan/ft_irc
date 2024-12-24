#include "../include/Command.hpp"
//done
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
	// 	int i = -1;
	// 	while (_server._clients[++i])
	// 	{
	// 		_server._clients[i].getNickname();
	// 		_server._clients[i].getUsername();
	// 		_server._clients[i].getRealname();
	// 	}
	// }
	// std::string mask = arg[0];
	// Channel *channel = _server.channels.find(mask);
	// if (channel)
	// {
		// print with checking is it in the cheannel
		// or print chanels clients if the channel stores clients
	// } else if (getIRCClient(mask))
	// {
	// 	clients.getNickname();
	// 	client.getUsername();
	// 	clients.getRealname();
	// } else 
		// throw ReplyException(ERR_NOSUCHNICK(mask));
}
