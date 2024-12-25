#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include "IRCMessage.hpp"
#include <string>

class Command
{
	public:
		Command(){};
		virtual ~Command(){};

		virtual void validate(Client *client, std::vector<std::string> arg){(void)client; (void)arg;};
		virtual void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels) = 0;
};

class Cap: public Command
{
	public:
		Cap();
		~Cap();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Invite: public Command
{
	public:
		Invite();
		~Invite();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Join: public Command
{
	public:
		Join();
		~Join();

		void validate(Client *client, std::vector<std::string> arg);
		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Kick: public Command
{
	public:
		Kick();
		~Kick();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Mode: public Command
{
	public:
		Mode();
		~Mode();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Nick: public Command
{
	public:
		Nick();
		~Nick();

		void validate(Client *client, std::vector<std::string> arg);
		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Notice: public Command
{
	public:
		Notice();
		~Notice();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Part: public Command
{
	public:
		Part();
		~Part();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Pass: public Command
{
	public:
		Pass();
		~Pass();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Ping: public Command
{
	public:
		Ping();
		~Ping();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Pong: public Command
{
	public:
		Pong();
		~Pong();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class PrivMsg: public Command
{
	public:
		PrivMsg();
		~PrivMsg();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Quit: public Command
{
	public:
		Quit();
		~Quit();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Topic: public Command
{
	public:
		Topic();
		~Topic();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class User: public Command
{
	public:
		User();
		~User();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};

class Who: public Command
{
	public:
		Who();
		~Who();

		void implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels);
};
#endif