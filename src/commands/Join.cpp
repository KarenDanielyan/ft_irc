#include "Command.hpp"

// JOIN <channel>{,<channel>} [<key>{,<key>}]

Join::Join()
{
}

Join::~Join()
{
}

// void Join::validate(Client *client, std::vector<std::string> arg)
// {
// 	std::string channel = IRCMessage.parameters[0]
// }


void Join::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message._parameters.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "JOIN"));
		return ;
	}
	std::string name = message._parameters[0];
	std::string pass = message._parameters.size() > 1 ? message._parameters[1] : "";
	std::string topic = "I exist because you wanted to.";
	Channel *channel = data.getChannel(name);
	//if the client is on the channel
	if (!channel)
	{
		data.addChannel(name, topic, pass, client);
		Channel* new_channel = data.getChannel(name);
		new_channel->addClient(client);
	}
	if (channel->isInviteOnly())
	{
		throw ReplyException(ERR_INVITEONLYCHAN(message._source, name));
		return ;
	}
	if (channel->getLimit() >= channel->getClientCount())
	{
		throw ReplyException(ERR_CHANNELISFULL(message._source, name));
		return ;
	}
	if (channel->getPassword() != pass)
	{
		throw ReplyException(ERR_BADCHANNELKEY(message._source, name));
		return ;
	}
	if (channel->isExist(client))
	{
		throw ReplyException(ERR_USERONCHANNEL(message._source, \
			client->getNickname()));
		return ;
	}
	server->reply(client->getConnection(), message._source + \
		client->getNickname() + " Joined " + \
		channel->getName() + " channel");
	//print about channel
	std::vector<Client *> clients = channel->getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); \
			it != clients.end(); ++it)
	{
		server->reply(client->getConnection(), RPL_NAMREPLY(message._source, \
			channel->getName(), \
			(*it)->getNickname()));
	}
	server->reply(client->getConnection(), RPL_ENDOFNAMES(message._source, \
		channel->getName()));

	if (channel->getTopic() != "")
		server->reply(client->getConnection(), message._source + \
			" Topic of channel: " + channel->getTopic());
	channel->addClient(client);
}
