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
#include "utils.hpp"

class Server;
class CClient;
class Command;

class CommandHandler
{
	private:
		Server* _server;
        std::map<std::string, Command *> _commands;
	public:
		CommandHandler(Server* server);
		~CommandHandler();

    void Handler(Client* Client, std::vector<std::string> arg, std::string cmd);
};

#endif