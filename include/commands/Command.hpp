/* ************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:11:58 by marihovh          #+#    #+#             */
/*   Updated: 2024/12/28 22:11:59 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************* */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "utils.hpp"
# include "IRCMessage.hpp"
# include "DAL.hpp"
# include <string>

class Command
{
	public:
		Command() {};
		virtual ~Command() {};

		virtual void validate(Client *client, IRCMessage& message) \
			{ (void)client; (void)message; }
		virtual void implement(Client *client, ITransport* server, \
			DAL& data, IRCMessage message) = 0;
};

class	IChannelCommand
{
	public:
		virtual void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const = 0;
};

class Cap: public Command
{
	public:
		Cap();
		~Cap();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Invite: public Command
{
	public:
		Invite();
		~Invite();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Join: public Command, public IChannelCommand
{
	public:
		Join();
		~Join();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void	validate(Client* client, IRCMessage& message);
		void	implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Kick: public Command, public IChannelCommand
{
	public:
		Kick();
		~Kick();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Mode: public Command, public IChannelCommand
{
	public:
		Mode();
		~Mode();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void	implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Nick: public Command
{
	public:
		Nick();
		~Nick();

		void	validate(Client *client, IRCMessage& message);
		void	implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Notice: public Command, public IChannelCommand
{
	public:
		Notice();
		~Notice();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Part: public Command, public IChannelCommand
{
	public:
		Part();
		~Part();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Pass: public Command
{
	public:
		Pass();
		~Pass();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Ping: public Command
{
	public:
		Ping();
		~Ping();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Pong: public Command
{
	public:
		Pong();
		~Pong();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class PrivMsg: public Command, public IChannelCommand
{
	public:
		PrivMsg();
		~PrivMsg();

		void broadcast(const ITransport* server, const Channel* to, \
			std::string const & message) const {
			IChannelCommand::broadcast(server, to, message);
		}
		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Quit: public Command
{
	public:
		Quit();
		~Quit();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Topic: public Command
{
	public:
		Topic();
		~Topic();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class User: public Command
{
	public:
		User();
		~User();

		void	validate(Client* client, IRCMessage& message);
		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};

class Who: public Command
{
	public:
		Who();
		~Who();

		void implement(Client *client, ITransport* server, DAL& data, \
			IRCMessage message);
};
#endif
