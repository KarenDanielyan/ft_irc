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
#include "defines.hpp"

DAL::~DAL()
{
	for (channel_iterator_t i = _channels.begin(); i != _channels.end(); i++)
		delete *i;
	for (clients_iterator_t i = _clients.begin(); i != _clients.end(); i++)
		delete i->second;
}

Client*	DAL::findClient(std::string nickname)
{
	for (clients_iterator_t it = _clients.begin(); \
		it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return NULL;
}


Client*	DAL::findClient(int fd)
{
	return (_clients[fd]);
}

std::map<int, Client *>& DAL::getClients(void)
{
	return (_clients);
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

void DAL::addChannel(std::string& name, std::string& topic, std::string& pass, Client* admin)
{
	Channel *channel = new Channel(name, topic, pass, admin);
	_channels.push_back(channel);
}

void	DAL::newClient(Connection* connection)
{
	_clients[connection->getFd()] = new Client(connection);
}

request_data_container_t&	DAL::getRequestDataContainer(void)
{
	return (_requests);
}
