#include "Command.hpp"

//<channel>{,<channel>} [<reason>]
Part::Part()
{
}

Part::~Part()
{
}

void Part::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message._parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "PART"));
		return;
	}
	std::string name = message._parameters[0].substr(1);

	Channel *channel = data.getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message._source, name));
		return;
	}
	if (!client->getChannel() || client->getChannel()->getName() != name)
	{
		throw ReplyException(ERR_NOTONCHANNEL(message._source, \
			client->getNickname()));
		return;
	}
	channel->removeClient(client);
	broadcast(server, channel, message._source + \
		client->getNickname() + " PART " + channel->getName());
}
