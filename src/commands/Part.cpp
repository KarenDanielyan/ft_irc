#include "Command.hpp"

//<channel>{,<channel>} [<reason>]
Part::Part(Server* server): Command(server)
{
}

Part::~Part()
{
}

void Partimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("PART"));
		return;
	}
	std::string name = arg[0].substr(1);

	Channel *channel = application->getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(name));
		return;
	}
	if (!client->getChannel() || client->getChannel()->getName() != name)
	{
		throw ReplyException(ERR_NOTONCHANNEL(client->getNickname()));
		return;
	}
	channel->removeClient(client);
	channel->broadcast(client->getNickname() + " PART " + channel->getName());
}
