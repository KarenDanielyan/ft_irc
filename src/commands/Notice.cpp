#include "Command.hpp"
//<target>{,<target>} <text to be sent>
Notice::Notice()
{
}

Notice::~Notice()
{
}

void Notice::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	if (message._parameters.size() < 2 || message._parameters[0].empty() || \
			message._parameters[1].empty())
		return;
	std::string target = message._parameters[0];
	std::string msg = "";
	for (unsigned long i = 1; i < message._parameters.size(); i++)
	{
		msg += message._parameters[i];
		msg += " ";
	}
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = data->getChannel(name);
		if (!channel)
			return ;
		if (!channel->isExist(client))
			return ;
		channel->broadcast(message._source + msg);
		return ;
	}	
	Client *dest = data->getClient(target);
	if (!dest)
		return;
	server->reply(client->getConnection(), (message._source + msg));
}
