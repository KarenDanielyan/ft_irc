#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "utils.hpp"
# include "IRCMessage.hpp"
# include "CommandHandler.hpp"
# include "Application.hpp"
# include <string>

class DataContainer;

class Command
{
	public:
		Command(){};
		virtual ~Command(){};

		virtual void validate(Client *client, IRCMessage message)
		{(void)client; (void)message;}
		virtual void implement(Client *client, ITransport* server, \
			DataContainer* data, IRCMessage message) = 0;
};

class Cap: public Command
{
	public:
		Cap();
		~Cap();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Invite: public Command
{
	public:
		Invite();
		~Invite();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Join: public Command
{
	public:
		Join();
		~Join();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Kick: public Command
{
	public:
		Kick();
		~Kick();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Mode: public Command
{
	public:
		Mode();
		~Mode();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Nick: public Command
{
	public:
		Nick();
		~Nick();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Notice: public Command
{
	public:
		Notice();
		~Notice();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Part: public Command
{
	public:
		Part();
		~Part();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Pass: public Command
{
	public:
		Pass();
		~Pass();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Ping: public Command
{
	public:
		Ping();
		~Ping();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Pong: public Command
{
	public:
		Pong();
		~Pong();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class PrivMsg: public Command
{
	public:
		PrivMsg();
		~PrivMsg();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Quit: public Command
{
	public:
		Quit();
		~Quit();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Topic: public Command
{
	public:
		Topic();
		~Topic();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class User: public Command
{
	public:
		User();
		~User();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};

class Who: public Command
{
	public:
		Who();
		~Who();

		void implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message);
};
#endif