#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ITransport* server, \
				std::map<int, Client*>& clients, \
				std::vector<Channel *>& channels)
{
	_server = server;
	_data = new DataContainer(clients, channels);
	_commands["CAP"] = new Cap();
	_commands["INVITE"] = new Invite();
	_commands["JOIN"] = new Join();
	_commands["KICK"] = new Kick();
	_commands["MODE"] = new Mode();
	_commands["NICK"] = new Nick();
	_commands["NOTICE"] = new Notice();
	_commands["PART"] = new Part();
	_commands["PASS"] = new Pass();
	_commands["PING"] = new Ping();
	_commands["PONG"] = new Pong();
	_commands["PRIVMSG"] = new PrivMsg();
	_commands["QUIT"] = new Quit();
	_commands["TOPIC"] = new Topic();
	_commands["USER"] = new User();
	_commands["WHO"] = new Who();
}

void CommandHandler::Handler(Client* client, IRCMessage message)
{
	std::map<std::string, Command*>::iterator it = _commands.find(message._command);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(message._command));
	else
		_commands[message._command]->implement(client, _server, _data, message);
}

DataContainer::DataContainer(std::map<int, Client *>& clients, \
		std::vector<Channel *>& channels): _clients(clients), _channels(channels)
{
}

DataContainer::~DataContainer()
{
}

Client*	DataContainer::getClient(std::string nick)
{
	for (Application::clients_iterator_t it = _clients.begin(); \
		it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nick)
			return it->second;
	}
	return NULL;
}

std::vector<Client *> DataContainer::getClients(void)
{
	std::vector<Client*> clientList;

	for (std::map<int, Client*>::iterator it = _clients.begin(); \
		it != _clients.end(); ++it)
	{
		clientList.push_back(it->second);
	}
	return clientList;
}

Channel* DataContainer::getChannel(std::string name)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); \
		it != _channels.end(); ++it)
	{
		if ((*it)->getName() == name)
			return (*it);
	}
	return NULL;
}

std::string const &	DataContainer::getPassword()
{
	return _password;
}
