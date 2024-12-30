/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:32 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/30 11:09:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "defines.hpp"
//done done
Who::Who()
{
}

Who::~Who()
{
}

void Who::implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message)
{
	std::string channel;
	if (message.parameters.empty())
	{
		std::map<int, Client*> clients = data.getClients();
		for (clients_iterator_t it = clients.begin(); it != clients.end(); it++)
		{
			channel = "";
			if (it->second->getChannel())
				channel = it->second->getChannel()->getName();
			server->reply(client->getConnection(), \
				RPL_WHOREPLY(message.source, 
				channel, \
				it->second->getUsername(), \
				it->second->getConnection()->getHostname(), \
				"ft_irc", \
				it->second->getNickname(), \
				" ", \
				it->second->getRealname()));
		}
		return ;
	}
	std::string mask = message.parameters[0];
	if (mask[0] == '#')
	{
		Channel *channel = data.getChannel(mask);
		if (!channel)
			throw ReplyException(ERR_NOSUCHCHANNEL(message.source, mask));
		std::vector<Client*> clients = channel->getClients();
		for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			server->reply((client)->getConnection(), \
				RPL_WHOREPLY(message.source, \
				mask, \
				(*it)->getUsername(), \
				(*it)->getConnection()->getHostname(), \
				"ft_irc", \
				(*it)->getNickname(), \
				" ", \
				(*it)->getRealname()));
		}
		server->reply(client->getConnection(), RPL_ENDOFWHO(message.source, \
			mask));
		return ;
	}
	Client *toPrint = data.findClient(mask);
	if (toPrint) {
		if (toPrint->getChannel())
			channel = toPrint->getChannel()->getName();
		else
			channel = "";
	}
	else
		throw ReplyException(ERR_NOSUCHNICK(message.source, mask));
	server->reply(client->getConnection(), \
			RPL_WHOREPLY(message.source, \
				channel, \
				toPrint->getUsername(), \
				toPrint->getConnection()->getHostname(), \
				"ft_irc", \
				toPrint->getNickname(), \
				" ", \
				toPrint->getRealname()));
	server->reply(client->getConnection(), RPL_ENDOFWHO(message.source, \
			mask));
}
