#include "Command.hpp"
//<target>{,<target>} <text to be sent>
Notice::Notice(Server* server): Command(server)
{
}

Notice::~Notice()
{
}

void Notice::implement(IRCClient* client, std::vector<std::string> arg)
{
	if (arg.size() < 2 || arg[0].empty() || arg[1].empty())
		return;
	std::string target = arg[0];
	std::string message = "";
	for (unsigned long i = 1; i < arg.size(); i++)
	{
		message += arg[i];
		message += " ";
	}
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = application.getChannel(name);
		if (!channel)
			return ;
		IRCClient toPrint = application.getClient(client);
		if (!toPrint)
			return ;
		channel.broadcast(message);
		return ;
	}	
	Client *dest = _server->getClient(target);
	if (!dest)
		return;
	client->SendMessage(client, message);
}
