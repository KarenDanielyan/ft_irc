#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Server.hpp"
#include "Client.hpp"
#include "Command.hpp"

class Server;
class Client;
class Command;

class CommandHandler
{
	private:
		Server* _server;
        std::map<std::string, Command *> _commands;
	public:
		CommandHandler(Server* server);
		~CommandHandler();

    void Handler(Client* client, std::vector<std::string> arg, std::string cmd);
};

#endif