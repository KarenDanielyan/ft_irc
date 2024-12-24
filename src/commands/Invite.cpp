#include "Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite(Server* server): Command(server)
{
}

Invite::~Invite()
{
}

void Invite::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (_arg.size() < 2)
	{
		throw ReplyException(NEEDMOREPARAMS());
		return ;
	}

	IRCClient* clientToInvite = _server->getUser(arg[0]);
	Channel* channelToInvite = _server->getChannel(arg[1]);

	if (!clientToInvite)
	{
		throw ReplyException(ERR_NOSUCHNICK(arg[0]));
		return ;
	}
	if (!channelToInvite)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(arg[1]));
		return ;
	}
	if (!client->getOpPerm())
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client));
		return ;
	}
	if (_server->getClient(clientToInvite))
	{
		throw ReplyException(ERR_USERONCHANNEL(clientToInvite));
		return ;
	}
	// if ()
	// check if the _IRCClient has the permision to invite
	// 
}
