#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <map>
# include "Server.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "utils.hpp"

class Server;
class Client;
class Command;

class DataContainer
{
	private:
		std::map<int, Client *>&			_clients;
		std::vector<Channel *>&				_channels;
		std::string							_password;
	public:
		DataContainer(std::map<int, Client *>& clients, \
			std::vector<Channel *>& channels);
		~DataContainer();

		Client*					getClient(std::string nick);
		std::vector<Client *>	getClients(void);
		Channel*				getChannel(std::string name);
		std::string const &		getPassword();

		void					addChannel(std::string name, std::string pass);
};

class CommandHandler
{
	private:
		ITransport*							_server;
		DataContainer*						_data;
		std::map<std::string, Command *>	_commands;
	public:
		CommandHandler(ITransport* server, std::map<int, Client *>& clients, \
			std::vector<Channel *>& channels);
		~CommandHandler();

	void Handler(Client* Client, IRCMessage message);
};

#endif
