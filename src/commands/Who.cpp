#include "../include/Command.hpp"
//done done
Who::Who(Server* server): Command(server)
{
}

Who::~Who()
{
}

void Who::implement(IRCClient* client, std::vector<std::string> arg)
{
	int i;
	if (arg.empty())
	{
		i = -1;
		while (application._clients[++i])
		{
			SendMessage(client, RPL_WHOREPLY(application._clients[i].getNickname(), \
				application._clients[i].getUsername(), application._clients[i].getRealname()));
		}
		return ;
	}
	std::string mask = arg[0];
	if (target[0] == '#')
	{
		Channel *channel = application.channels.find(mask);
		if (!channel)
		{
			throw ReplyException(ERR_NOSUCHCHAN(mask));
			return ;
		}
		std::vector<IRCClient*> clients = channel.getClients();
		i = -1;
		while (clients[++i])
		{
			SendMessage(client, RPL_WHOREPLY(clients[i].getNickname(), \
				clients[i].getUsername(), clients[i].getRealname()));
		}
		return ;
	}
	IRCClient toPrint = application.getClient(mask);
	if (!toPrint)
	{
		throw ReplyException(ERR_NOSUCHNICK(mask));
		return ;
	}
	SendMessage(client, RPL_WHOREPLY(toPrint.getNickname(), \
			toPrint.getUsername(), toPrint.getRealname()));
}
