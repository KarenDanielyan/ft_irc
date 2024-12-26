/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:38:34 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 00:10:34 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ITransport* server, \
				std::map<int, Client*>& clients, \
				std::vector<Channel *>& channels)
{
	_server = server;
	_data = new DAL(clients, channels);
	_commands["CAP"] = new Cap();
}

void CommandHandler::handle(Client* client, IRCMessage message)
{
	std::map<std::string, Command*>::iterator it = _commands.find(message._command);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(message._source, \
			message._command));
	else
		_commands[message._command]->implement(client, _server, _data, message);
}
