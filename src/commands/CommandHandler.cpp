/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariam <mariam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:38:34 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 01:38:10 by mariam           ###   ########.fr       */
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
	commands_iterator_t it = _commands.find(message._command);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(message._source, \
			message._command));
	else
		_commands[message._command]->implement(client, _server, _data, message);
}
