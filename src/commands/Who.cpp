#include "../include/Command.hpp"
//done done
Who::Who()
{
}

Who::~Who()
{
}

void Who::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	int i;
	if (message._parameters.empty())
	{
		std::vector<Client*> clients = data->getClients();
		i = -1;
		while (clients[++i])
		{
			server->reply(client->getConnection(), \
				RPL_WHOREPLY(clients[i]->getNickname(), \
				clients[i]->getUsername(), clients[i]->getRealname()));
		}
		return ;
	}
	std::string mask = message._parameters[0];
	if (mask[0] == '#')
	{
		mask = mask.substr(1);
		Channel *channel = data->getChannel(mask);
		if (!channel)
		{
			throw ReplyException(ERR_NOSUCHCHANNEL(mask));
			return ;
		}
		std::vector<Client*> clients = channel->getClients();
		i = -1;
		while (clients[++i])
		{
			server->reply(client->getConnection(), \
				RPL_WHOREPLY(clients[i]->getNickname(), \
				clients[i]->getUsername(), clients[i]->getRealname()));
		}
		return ;
	}
	Client *toPrint = data->getClient(mask);
	if (!toPrint)
	{
		throw ReplyException(ERR_NOSUCHNICK(mask));
		return ;
	}
	server->reply(client->getConnection(), \
			RPL_WHOREPLY(toPrint->getNickname(), \
			toPrint->getUsername(), toPrint->getRealname()));
}
