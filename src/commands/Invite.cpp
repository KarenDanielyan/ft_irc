#include "Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite()
{
}

Invite::~Invite()
{
}

void Invite::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	if (message._parameters.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("INVITE"));
		return ;
	}

	Client* clientToInvite = data->getClient(message._parameters[0]);
	Channel* channelToInvite = data->getChannel(message._parameters[1]);

	if (!clientToInvite)
	{
		throw ReplyException(ERR_NOSUCHNICK(message._parameters[0]));
		return ;
	}
	if (!channelToInvite)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message._parameters[1]));
		return ;
	}
	if (!channelToInvite->isInvited(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	channelToInvite->setInvite(clientToInvite);
	server->reply(clientToInvite->getConnection(), RPL_INVITING(clientToInvite->getNickname(),
		channelToInvite->getName()));
}
