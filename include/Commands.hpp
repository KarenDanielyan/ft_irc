#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Server.hpp"
#include "Client.hpp"

class Server;
class Client;

class Commands
{
	private:
		Server* _server;
	public:
		Commands(Server* _server);
		~Commands();

		void Cap(Client* _client, std::vector<std::string> _arg);
        void Who(Client* _client, std::vector<std::string> _arg);
		void Pass(Client* _client, std::vector<std::string> _arg);
        void Join(Client* _client, std::vector<std::string> _arg);
        void Kick(Client* _client, std::vector<std::string> _arg);
        void Mode(Client* _client, std::vector<std::string> _arg);
        void Quit(Client* _client, std::vector<std::string> _arg);
        void Nick(Client* _client, std::vector<std::string> _arg);
        void Pong(Client* _client, std::vector<std::string> _arg);
        void Ping(Client* _client, std::vector<std::string> _arg);
        void Part(Client* _client, std::vector<std::string> _arg);
        void Topic(Client* _client, std::vector<std::string> _arg);
        void Notice(Client* _client, std::vector<std::string> _arg);
        void Invite(Client* _client, std::vector<std::string> _arg);
        void PrivMsg(Client* _client, std::vector<std::string> _arg);
        void UserCmd(Client* _client, std::vector<std::string> _arg);
		void handler(Client* _client, std::vector<std::string> _arg, std::string _cmd);
};

#endif