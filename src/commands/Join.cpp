#include "../include/Command.hpp"

// JOIN <channel>{,<channel>} [<key>{,<key>}]

Join::Join(Server* server): Command(server)
{
}

Join::~Join()
{
}

void Join::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("JOIN"));
		return ;
	}
	std::string name = arg[0];
	std::string pass = arg.size() > 1 ? arg[1] : "";
	Channel *channel = _server.getChannel(name);
	//if the client is on the channel
	// if (!channel)
		// create channel name
		// set client as admin
	if (channel->InviteOnly())
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
	if (channel->isExist(user))
	{
		throw ReplyException(ERR_USERONCHANNEL(client->getNickname()));
		return ;
	}
	//print about channel
	std::vector<User *> users = channel->getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
		//print to user RPL_NAMREPLY(user->getNickname(), name, " ", (*it)->getNickname()));
	if (channel->getTopic != "")
		//print to user RPL_TOPIC(user->getNickname(), name, channel->getTopic()));
	channel->addCLient(client);
}
