/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:32 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:33 by marihovh         ###   ########.fr       */
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
	int i;
	if (message.parameters.empty())
	{
		std::map<int, Client*> clients = data.getClients();
		for (clients_iterator_t it = clients.begin(); it != clients.end(); it++)
		{
			server->reply(client->getConnection(), \
				RPL_WHOREPLY(message.source, it->second->getNickname(), \
				it->second->getUsername(), it->second->getRealname()));
		}
		return ;
	}
	std::string mask = message.parameters[0];
	if (mask[0] == '#')
	{
		mask = mask.substr(1);
		Channel *channel = data.getChannel(mask);
		if (!channel)
			throw ReplyException(ERR_NOSUCHCHANNEL(message.source, mask));
		std::vector<Client*> clients = channel->getClients();
		i = -1;
		while (clients[++i])
		{
			server->reply(client->getConnection(), \
				RPL_WHOREPLY(message.source, clients[i]->getNickname(), \
				clients[i]->getUsername(), clients[i]->getRealname()));
		}
		return ;
	}
	Client *toPrint = data.findClient(mask);
	if (!toPrint)
		throw ReplyException(ERR_NOSUCHNICK(message.source, mask));
	server->reply(client->getConnection(), \
			RPL_WHOREPLY(message.source, toPrint->getNickname(), \
			toPrint->getUsername(), toPrint->getRealname()));
}
