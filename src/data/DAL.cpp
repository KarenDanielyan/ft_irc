/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariam <mariam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:33:34 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 02:03:36 by mariam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DAL.hpp"

DAL::DAL(std::map<int, Client *>& clients, \
		std::vector<Channel *>& channels): _clients(clients), _channels(channels)
{}

DAL::~DAL() {}

Client*	DAL::getClient(std::string nick)
{
	for (clients_iterator_t it = _clients.begin(); \
		it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nick)
			return it->second;
	}
	return NULL;
}

std::vector<Client *> DAL::getClients(void)
{
	std::vector<Client*> clientList;

	for (std::map<int, Client*>::iterator it = _clients.begin(); \
		it != _clients.end(); ++it)
	{
		clientList.push_back(it->second);
	}
	return clientList;
}

Channel* DAL::getChannel(std::string name)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); \
		it != _channels.end(); ++it)
	{
		if ((*it)->getName() == name)
			return (*it);
	}
	return NULL;
}

std::string const &	DAL::getPassword()
{
	return _password;
}
// data->addChannel(name, "", pass, client);

void DAL::addChannel(std::string name, std::string topic, std::string pass, Client* admin)
{
	Channel *channel = new Channel(name, topic, pass, admin);
	_channels.push_back(channel);
}