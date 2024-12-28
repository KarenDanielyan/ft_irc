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
	if (message.parameters.size() < 2)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, \
			"INVITE"));
		return ;
	}

	Client* clientToInvite = data.findClient(message.parameters[0]);
	Channel* channelToInvite = data.getChannel(message.parameters[1]);

	if (!clientToInvite)
	{
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			message.parameters[0]));
		return ;
	}
	if (!channelToInvite)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, \
			message.parameters[1]));
		return ;
	}
	if (!channelToInvite->isInvited(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
		return ;
	}
	channelToInvite->setInvite(clientToInvite);
	server->reply(clientToInvite->getConnection(), \
		RPL_INVITING(message.source, clientToInvite->getNickname(),
		channelToInvite->getName()));
}
