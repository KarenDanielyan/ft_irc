/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IChannelCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:10:31 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:10:32 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"

void IChannelCommand::broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const
{
	std::vector<Client*>	clients = to->getClients();
	for (Channel::clientlist_iterator_t it = clients.begin(); it != clients.end(); it++)
		server->reply((*it)->getConnection(), message);
}
