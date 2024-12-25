#include "Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite(Server* server): Command(server)
{
}

Invite::~Invite()
{
}

void Invite::implement(Client* client, std::vector<std::string> arg)
{
	if (arg.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("PASS"));
		return ;
	}

	Client* clientToInvite = application->getClient(arg[0]);
	Channel* channelToInvite = application->getChannel(arg[1]);

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
	if (!channelToInvite->isInvited(*client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	if (application->getClient(clientToInvite))
	{
		throw ReplyException(ERR_USERONCHANNEL(channelToInvite->getName()));
		return ;
	}
	channelToInvite->setInvite(clientToInvite);
	SendMessage(clientToInvite, RPL_INVITING(clientToInvite->getNickname(), channelToInvite->getName()));
}
