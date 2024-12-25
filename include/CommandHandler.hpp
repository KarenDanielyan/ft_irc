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

class CommandHandler
{
	private:
		ITransport* _server;
		std::vector<Channel *>				_channels;
		std::map<int, Client *>&			_clients;
		std::map<std::string, Command *>	_commands;
	public:
		CommandHandler(ITransport* server, std::map<int, Client*>& _clients, \
				std::vector<Channel *>& _channels);
		~CommandHandler();

	void Handler(Client* Client, std::vector<std::string> arg, std::string cmd);
};

#endif
