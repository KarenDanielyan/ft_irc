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

class CommandHandler
{
	private:
		ITransport*							_server;
		DAL*						_data;
		std::map<std::string, Command *>	_commands;
	public:
		CommandHandler(ITransport* server, std::map<int, Client *>& clients, \
			std::vector<Channel *>& channels);
		~CommandHandler();

	void handle(Client* Client, IRCMessage message);
};

#endif
