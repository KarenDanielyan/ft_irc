#include "../include/Command.hpp"
//done done
Who::Who(Server* server): Command(server)
{
}

Who::~Who()
{
}

void Who::implement(Client* client, std::vector<std::string> arg)
{
	int i;
	if (arg.empty())
	{
		std::vector<Client*> clients = application->getClients();
		i = -1;
		while (clients[++i])
		{
			SendMessage(client, RPL_WHOREPLY(clients[i]->getNickname(), \
				clients[i]->getUsername(), clients[i]->getRealname()));
		}
		return ;
	}
	std::string mask = arg[0];
	if (mask[0] == '#')
	{
		mask = mask.substr(1);
		Channel *channel = application->getChannel(mask);
		if (!channel)
		{
			throw ReplyException(ERR_NOSUCHCHANNEL(mask));
			return ;
		}
		std::vector<Client*> clients = channel->getClients();
		i = -1;
		while (clients[++i])
		{
			SendMessage(client, RPL_WHOREPLY(clients[i]->getNickname(), \
				clients[i]->getUsername(), clients[i]->getRealname()));
		}
		return ;
	}
	Client *toPrint = application->getClient(mask);
	if (!toPrint)
	{
		throw ReplyException(ERR_NOSUCHNICK(mask));
		return ;
	}
	SendMessage(client, RPL_WHOREPLY(toPrint->getNickname(), \
			toPrint->getUsername(), toPrint->getRealname()));
}
