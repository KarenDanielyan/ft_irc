#include "Channel.hpp"
// Channel(std::string name, std::string topic, std::string pass, \
// 			ITransport* server);

Channel::Channel(std::string name, std::string topic, std::string pass, ITransport* server, Client* admin): \
	_server(server), _name(name), _topic(topic), _password(pass), _admin(admin)
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

void Channel::setTopic(std::string topic) {
	_topic = topic;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
}

void Channel::addOperator(Client *client)
{
	_clients.push_back(client);
}

bool Channel::isExist(Client *client)
{
	std::vector<Client*>::const_iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
		return false;
	return true;
}

void Channel::removeClient(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		delete client;
	}
}

void Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		delete client;
	}
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

void Channel::broadcast(std::string message) const
{
	int i = -1;
	while (_clients[++i])
		_server->reply(_clients[i]->getConnection(), message);
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
	return _inviteList.empty();
}
