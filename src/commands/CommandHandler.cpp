#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ITransport* server, \
				std::map<int, Client*>& clients, \
				std::vector<Channel *>& channels) : \
	_server(server), _channels(channels), _clients(clients)
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

void CommandHandler::Handler(Client* client, std::vector<std::string> arg, \
							 std::string cmd)
{
	std::map<std::string, Command*>::iterator it = _commands.find(cmd);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(cmd));
	else
		_commands[cmd]->implement(client, arg, _client, _channels, _server);
}
