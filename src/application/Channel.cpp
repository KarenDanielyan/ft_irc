#include "Channel.hpp"

Channel::Channel(std::string name, std::string topic): _name(name), \
	_topic(topic), _clientLimit(0), _password("")
{
}

Channel::~Channel()
{
	std::vector<IRCClient*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete *it;
	_clients.clear();
}

std::string Channel::getName() const
{
	return _name;
}

std::string Channel::getTopic() const
{
	return _topic;
}

std::string Channel::getPass() const 
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

std::vector<IRCClient*> Channel::getClients() const {
	return _clients;
}


void Channel::setName(std::string name) {
	_name = name;
}

void Channel::setPass(std::string pass) {
	_password = pass;
}

void Channel::setTopic(std::string topic) {
	_topic = topic;
}

void Channel::addClient(IRCClient *client)
{
	// if (_clientLimit > 0 && static_cast<int>(_clients.size()) >= _clientLimit) {
	// 	throw std::runtime_error("Client limit reached. Cannot add more clients.");
	// }
	// // Check if the client already exists
	// if (std::find(_clients.begin(), _clients.end(), client) != _clients.end()) {
	// 	throw std::runtime_error("Client already exists in the channel.");
	// }
	_clients.push_back(client);
}

bool Channel::isExist(IRCClient* client) const
{
	return std::find(_clients.begin(), _clients.end(), client) != _clients.end();
}

void Channel::removeClient(IRCClient* client)
{
	std::vector<IRCClient*>::iterator it = std::find(clients.begin(), clients.end(), client);
	if (it != clients.end()) {
		clients.erase(it);
		delete client;
	}
}