/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:12:21 by marihovh          #+#    #+#             */
/*   Updated: 2025/01/02 23:07:25 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, std::string topic, std::string pass, Client* admin): \
	_name(name), _topic(topic), _password(pass), _admin(admin), _clientLimit(0)
{
}

Channel::~Channel()
{
	std::vector<Client*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete *it;
	_clients.clear();
}

void Channel::setAdmin(Client* admin)
{
	_admin = admin;
}

std::string Channel::getName() const
{
	return _name;
}

std::string Channel::getTopic() const
{
	return _topic;
}

bool Channel::isAdmin(Client *client)
{
	return client->getNickname() == _admin->getNickname();
}

std::string Channel::getPassword() const 
{
	return _password;
}

int Channel::getClientCount() const 
{
	return _clients.size();
}

int Channel::getLimit() const 
{
	return _clientLimit;
}

std::vector<Client*> Channel::getClients() const {
	return _clients;
}

void Channel::setName(std::string name) {
	_name = name;
}

void Channel::setPassword(std::string pass) {
	_password = pass;
}

void Channel::setTopic(std::string &topic) {
	_topic = topic;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
}

void Channel::addOperator(Client *client)
{
	_operators.push_back(client);
}

void Channel::addTopicOperator(Client *client)
{
	_topicOperators.push_back(client);
}

bool Channel::isExist(Client *client)
{
	std::vector<Client*>::const_iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it == _clients.end())
		return false;
	return true;
}

void Channel::removeClient(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
		_clients.erase(it);
}

void Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end())
		_operators.erase(it);
}

void Channel::removeTopicOperator(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_topicOperators.begin(), _topicOperators.end(), client);
	if (it != _topicOperators.end())
		_topicOperators.erase(it);
}

std::vector<std::string> Channel::getNicknames() const
{
	std::vector<std::string> nicknames;
	unsigned long i = 0;
	while (i++ < _clients.size())
		nicknames.push_back(_clients[i]->getNickname());
	return nicknames;
}

void Channel::setLimit(unsigned long limit)
{
	_clientLimit = limit;
}

void Channel::setOnlyInvite(bool OnlyInvite)
{
	_onlyInvite = OnlyInvite;
}

bool Channel::isOperator(Client* client)
{
	return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}

bool Channel::isTopicOperator(Client* client)
{
	return std::find(_topicOperators.begin(), _topicOperators.end(), client) != _topicOperators.end();
}

bool Channel::isInvited(Client* client)
{
	return std::find(_inviteList.begin(), _inviteList.end(), client) != _inviteList.end();
}

void Channel::setInvite(Client *client)
{
	_inviteList.push_back(client);
}

bool Channel::isInviteOnly()
{
	return _onlyInvite;
}
