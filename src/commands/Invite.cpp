#include "Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite()
{
}

Invite::~Invite()
{
}

void Invite::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message._parameters.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, \
			"INVITE"));
		return ;
	}

	Client* clientToInvite = data.findClient(message._parameters[0]);
	Channel* channelToInvite = data.getChannel(message._parameters[1]);

	if (!clientToInvite)
	{
		throw ReplyException(ERR_NOSUCHNICK(message._source, \
			message._parameters[0]));
		return ;
	}
	if (!channelToInvite)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message._source, \
			message._parameters[1]));
		return ;
	}
	if (!channelToInvite->isInvited(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message._source, \
			client->getNickname()));
		return ;
	}
	channelToInvite->setInvite(clientToInvite);
	server->reply(clientToInvite->getConnection(), \
		RPL_INVITING(message._source, clientToInvite->getNickname(),
		channelToInvite->getName()));
}
