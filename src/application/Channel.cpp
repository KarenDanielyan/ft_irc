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
	_clients.push_back(client);
}

void Channel::addOperator(IRCClient *client)
{
	_clients.push_back(client);
}

bool Channel::isExist(IRCClient* client) const
{
	return std::find(_clients.begin(), _clients.end(), client) != _clients.end();
}

void Channel::removeClient(IRCClient* client)
{
	std::vector<IRCClient*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		delete client;
	}
}

void Channel::removeOperator(IRCClient* client)
{
	std::vector<IRCClient*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		delete client;
	}
}

std::vector<std::string> Channel::getNicknames() const
{
	std::vector<std::string> nicknames;
	for (const IRCClient& client : clients)
		nicknames.push_back(client.getNickname());
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

bool Channel::isOperator(IRCClient client)
{
	return std::find(_operators.begin(), _operators.end(), client);
}


void Channel::broadcast(std::string message) const
{
	i = -1;
	while (clients[++i])
		SendMessage(client, message);
}