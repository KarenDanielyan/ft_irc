#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "Server.hpp"
#include "IRCClient.hpp"
#include "utils.hpp"
#include <string>

class Command
{
	protected:
		Server* _server;
	public:
		Command(Server* server): _server(server){};
		virtual ~Command(){};

		virtual void implement(IRCClient *IRCClient, std::vector<std::string> arg) = 0;
};

class Cap: public Command
{
	public:
		Cap(Server *server);
		~Cap();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Invite: public Command
{
	public:
		Invite(Server *server);
		~Invite();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Join: public Command
{
	public:
		Join(Server *server);
		~Join();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Kick: public Command
{
	public:
		Kick(Server *server);
		~Kick();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Mode: public Command
{
	public:
		Mode(Server *server);
		~Mode();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Nick: public Command
{
	public:
		Nick(Server *server);
		~Nick();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Notice: public Command
{
	public:
		Notice(Server *server);
		~Notice();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Part: public Command
{
	public:
		Part(Server *server);
		~Part();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Pass: public Command
{
	public:
		Pass(Server *server);
		~Pass();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Ping: public Command
{
	public:
		Ping(Server *server);
		~Ping();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Pong: public Command
{
	public:
		Pong(Server *server);
		~Pong();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class PrivMsg: public Command
{
	public:
		PrivMsg(Server *server);
		~PrivMsg();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Quit: public Command
{
	public:
		Quit(Server *server);
		~Quit();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Topic: public Command
{
	public:
		Topic(Server *server);
		~Topic();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class User: public Command
{
	public:
		User(Server *server);
		~User();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};

class Who: public Command
{
	public:
		Who(Server *server);
		~Who();

		void implement(IRCClient *IRCClient, std::vector<std::string> arg);
};
#endif