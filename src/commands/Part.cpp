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
	if (message.parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "PART"));
		return;
	}
	std::string name = message.parameters[0].substr(1);

	Channel *channel = data.getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, name));
		return;
	}
	if (!client->getChannel() || client->getChannel()->getName() != name)
	{
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
		return;
	}
	channel->removeClient(client);
	broadcast(server, channel, message.source + \
		client->getNickname() + " PART " + channel->getName());
}
