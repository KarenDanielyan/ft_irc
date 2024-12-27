/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:15:40 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 00:19:46 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"

void IChannelCommand::broadcast(const ITransport* server, Channel* to, \
			std::string const & message) const
{
	std::vector<Client*>	clients = to->getClients();
	for (Channel::clientlist_iterator_t it = clients.begin(); it != clients.end(); it++)
		server->reply((*it)->getConnection(), message);
}
