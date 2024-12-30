/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:10:37 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 13:44:07 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite()
{
}

Invite::~Invite()
{
}

void Invite::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 2)
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, \
			"INVITE"));
	Client* clientToInvite = data.findClient(message.parameters[0]);
	Channel* channelToInvite = data.getChannel(message.parameters[1]);

	if (!clientToInvite)
		throw ReplyException(ERR_NOSUCHNICK(message.source, \
			message.parameters[0]));
	if (!channelToInvite)
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, \
			message.parameters[1]));
	if (client->getChannel()->getName() != channelToInvite->getName())
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
	if (clientToInvite->getChannel()->getName() == channelToInvite->getName())
		throw ReplyException(ERR_USERONCHANNEL(message.source, \
			clientToInvite->getNickname(), channelToInvite->getName()));
	if (!channelToInvite->isOperator(client))
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
	channelToInvite->setInvite(clientToInvite);
	server->reply(clientToInvite->getConnection(), \
		RPL_INVITING(message.source, clientToInvite->getNickname(),
		channelToInvite->getName()));
}
