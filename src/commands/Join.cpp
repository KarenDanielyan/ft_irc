#include "Command.hpp"

// JOIN <channel>{,<channel>} [<key>{,<key>}]

Join::Join(Server* server): Command(server)
{
}

Join::~Join()
{
}
void Join::validate(Client *client, std::vector<std::string> arg)
{
	std::string channel = IRCMessage.parameters[0]
	if ( channel[0] != '#' || channel[0] != '&')
		throw ERR_BADCHANMASK(channel);
}


void Join::implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("JOIN"));
		return ;
	}
	std::string name = arg[0];
	std::string pass = arg.size() > 1 ? arg[1] : "";
	Channel *channel = application->getChannel(name);
	//if the client is on the channel
	if (!channel)
	{
		application->addChannel(name, pass);
		new_channel = application->getChannel(name);
		new_channel->addClient(client);
	}
	if (channel->isInviteOnly())
	{
		throw ReplyException(ERR_INVITEONLYCHAN(name));
		return ;
	}
	if (channel->getLimit() >= channel->getClientCount())
	{
		throw ReplyException(ERR_CHANNELISFULL(name));
		return ;
	}
	if (channel->getPass() != pass)
	{
		throw ReplyException(ERR_BADCHANNELKEY(name));
		return ;
	}
	if (channel->isExist(*client))
	{
		throw ReplyException(ERR_USERONCHANNEL(client->getNickname()));
		return ;
	}
	sendMessage(client, client->getNickname() + " Joined " + channel->getName() + " channel");
	//print about channel
	std::vector<Client *> clients = channel->getClients();
	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
		sendMessage(client, RPL_NAMREPLY(channel->getName(), (*it)->getNickname()));
	sendMessage(client, RPL_ENDOFNAMES(channel->getName()));
	if (channel->getTopic() != "")
		sendMessage(client, "Topic of channel: " + channel->getTopic());
	channel->addClient(client);
}
