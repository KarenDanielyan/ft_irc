#include "Command.hpp"
//done
Kick::Kick()
{
}

Kick::~Kick()
{
}
//<channel> <user> *( "," <user> ) [<comment>]
void Kick::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	(void)server;
	if (message._parameters.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("KICK"));
		return;
	}
	std::string name = message._parameters[0].substr(1);
	std::string target = message._parameters[1];
	std::string msg = "Reason: ";
	Channel* channel = data->getChannel(name);
	unsigned long i = 1;
	while (++i <= message._parameters.size())
		msg += message._parameters[i];
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("KICK"));
		return ;
	}
	Client *dest = data->getClient(target);
	if (!dest)
	{
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	if (!dest->getChannel())
	{
		throw ReplyException(ERR_USERNOTINCHANNEL(dest->getNickname()));
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	channel->broadcast("from "+ channel->getName() + " removed " + \
		dest->getNickname() + " " + msg);
	channel->removeClient(dest);
}
