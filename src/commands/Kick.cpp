#include "../include/Command.hpp"
//done
Kick::Kick(Server* server): Command(server)
{
}

Kick::~Kick()
{
}
//<channel> <user> *( "," <user> ) [<comment>]
void Kick::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	if (arg.size() < 2 || arg[0].empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS(client->getNickname() + "Kick"));
		return;
	}
	td::string target = arg[0].substr(1);
	std::string channel = target.substr(1);
	std::vector<Channel* >::iterator	i;
			
	for (i = channels.begin(); i != channels.end(); i++)
		if (*i == target)
			break;
	if (arg[0] != '#' || i == channels.end())
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(target));
		return ;
	}
	std::string dest = target;
	// Client *dest = _server->getClient(target);
	if (dest.empty()) {
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	if (!dest->getChannel(channel))
		throw ReplyException(ERR_USERNOTINCHANNEL(dest->getNickname()));
	//if it was admin set adin another
	channel->removeUser(dest);
}
