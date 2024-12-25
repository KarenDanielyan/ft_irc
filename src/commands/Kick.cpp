#include "Command.hpp"
//done
Kick::Kick(Server* server): Command(server)
{
}

Kick::~Kick()
{
}
//<channel> <user> *( "," <user> ) [<comment>]
void Kick::implement(Client* client, std::vector<std::string> arg)
{
	if (arg.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("KICK"));
		return;
	}
	std::string name = arg[0].substr(1);
	std::string target = arg[1];
	std::string message = "";
	Channel* channel = aplication->getChannel(name);
	unsigned long i = 1;
	while (++i <= arg.size())
		message += arg[i];
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("KICK"));
		return ;
	}
	Client *dest = application->getClient(target);
	if (!dest)
	{
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	if (!dest->getChannel())
	{
		throw ReplyException(ERR_USERNOTINCHANNEL(dest->getNickname()));
	}
	if (!channel->isOperator(*client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	channel->broadcast("from "+ channel->getName() + " removed " + dest->getNickname());
	channel->removeClient(dest);
}
