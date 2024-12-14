#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "Server.hpp"
#include "Client.hpp"
#include <string>

class Command
{
	protected:
		Server* _server;
	public:
		Command(Server* server): _server(server){};
		virtual ~Command(){};

		virtual void implement(Client *client, std::vector<std::string> arg) = 0;
};

class Cap: public Command
{
	public:
		Cap(Server *server);
		~Cap();

		void implement(Client *client, std::vector<std::string> arg);
};

class Invite: public Command
{
	public:
		Invite(Server *server);
		~Invite();

		void implement(Client *client, std::vector<std::string> arg);
};

class Join: public Command
{
	public:
		Join(Server *server);
		~Join();

		void implement(Client *client, std::vector<std::string> arg);
};

class Kick: public Command
{
	public:
		Kick(Server *server);
		~Kick();

		void implement(Client *client, std::vector<std::string> arg);
};

class Mode: public Command
{
	public:
		Mode(Server *server);
		~Mode();

		void implement(Client *client, std::vector<std::string> arg);
};

class Nick: public Command
{
	public:
		Nick(Server *server);
		~Nick();

		void implement(Client *client, std::vector<std::string> arg);
};

class Notice: public Command
{
	public:
		Notice(Server *server);
		~Notice();

		void implement(Client *client, std::vector<std::string> arg);
};

class Part: public Command
{
	public:
		Part(Server *server);
		~Part();

		void implement(Client *client, std::vector<std::string> arg);
};

class Pass: public Command
{
	public:
		Pass(Server *server);
		~Pass();

		void implement(Client *client, std::vector<std::string> arg);
};

class Ping: public Command
{
	public:
		Ping(Server *server);
		~Ping();

		void implement(Client *client, std::vector<std::string> arg);
};

class Pong: public Command
{
	public:
		Pong(Server *server);
		~Pong();

		void implement(Client *client, std::vector<std::string> arg);
};

class PrivMsg: public Command
{
	public:
		PrivMsg(Server *server);
		~PrivMsg();

		void implement(Client *client, std::vector<std::string> arg);
};

class Quit: public Command
{
	public:
		Quit(Server *server);
		~Quit();

		void implement(Client *client, std::vector<std::string> arg);
};

class Topic: public Command
{
	public:
		Topic(Server *server);
		~Topic();

		void implement(Client *client, std::vector<std::string> arg);
};

class UserCmd: public Command
{
	public:
		UserCmd(Server *server);
		~UserCmd();

		void implement(Client *client, std::vector<std::string> arg);
};

class Who: public Command
{
	public:
		Who(Server *server);
		~Who();

		void implement(Client *client, std::vector<std::string> arg);
};
#endif