#include "Command.hpp"
//done
Kick::Kick()
{
}

Kick::~Kick()
{
}
//<channel> <user> *( "," <user> ) [<comment>]
void Kick::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	(void)server;
	if (message.parameters.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "KICK"));
		return;
	}
	std::string name = message.parameters[0].substr(1);
	std::string target = message.parameters[1];
	std::string msg = "Reason: ";
	Channel* channel = data.getChannel(name);
	unsigned long i = 1;
	while (++i <= message.parameters.size())
		msg += message.parameters[i];
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "KICK"));
		return ;
	}
	Client *dest = data.findClient(target);
	if (!dest)
	{
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			client->getNickname()));
		return;
	}
	if (!dest->getChannel())
	{
		throw ReplyException(ERR_USERNOTINCHANNEL(message.source, \
			dest->getNickname()));
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
		return ;
	}
	broadcast(server, channel, message.source + " from "+ channel->getName() \
		+ " removed " + dest->getNickname() + " " + msg);
	channel->removeClient(dest);
}
