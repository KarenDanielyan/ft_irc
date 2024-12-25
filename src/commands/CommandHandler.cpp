#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ITransport* server, \
				std::map<int, Client*>& clients, \
				std::vector<Channel *>& channels)
{
	_server = server;
	_data = new DataContainer(clients, channels);
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

void CommandHandler::Handler(Client* client, IRCMessage message)
{
	std::map<std::string, Command*>::iterator it = _commands.find(message._command);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(message._command));
	else
		_commands[message._command]->implement(client, _server, _data, message);
}
