/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:38:34 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 15:02:11 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"
#include "Command.hpp"

CommandHandler::CommandHandler(ITransport* server, DAL & data): _server(server), _data(data)
{
	_commands["CAP"] = new Cap();
	_commands["INVITE"] = new Invite();
	_commands["JOIN"] = new Join();
	_commands["KICK"] = new Kick();
	_commands["MODE"] = new Mode();
	_commands["NICK"] = new Nick();
	_commands["NOTICE"] = new Notice();
	_commands["PART"] = new Part();
	_commands["PASS"] = new Pass();
	_commands["PING"] = new Ping();
	_commands["PONG"] = new Pong();
	_commands["PRIVMSG"] = new PrivMsg();
	_commands["QUIT"] = new Quit();
	_commands["TOPIC"] = new Topic();
	_commands["USER"] = new User();
	_commands["WHO"] = new Who();
}

void CommandHandler::handle(Client* client, IRCMessage message)
{
	commands_iterator_t it = _commands.find(message.command);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(message.source, \
			message.command));
	else
	{
		if ((message.command != "PASS" && message.command != "NICK" && message.command != "USER") && client->getState() != Client::LIVE)
		{
			_server->reply(client->getConnection(), "You are not registrated");
			return ;
		}
		_commands[message.command]->implement(client, _server, _data, message);
	}
}

CommandHandler::~CommandHandler(void)
{
	for (commands_iterator_t it = _commands.begin(); it != _commands.end(); it++)
	{
		delete it->second;
	}
}

