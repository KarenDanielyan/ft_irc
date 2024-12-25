#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ITransport* server, \
				std::map<int, Client*>& clients, \
				std::vector<Channel *>& channels) : \
	_server(server), _channels(channels), _clients(clients)
{
	_commands["CAP"] = new Cap(server);
	_commands["INVITE"] = new Invite(server);
	_commands["JOIN"] = new Join(server);
	_commands["KICK"] = new Kick(server);
	_commands["MODE"] = new Mode(server);
	_commands["NICK"] = new Nick(server);
	_commands["NOTICE"] = new Notice(server);
	_commands["PART"] = new Part(server);
	_commands["PASS"] = new Pass(server);
	_commands["PING"] = new Ping(server);
	_commands["PONG"] = new Pong(server);
	_commands["PRIVMSG"] = new PrivMsg(server);
	_commands["QUIT"] = new Quit(server);
	_commands["TOPIC"] = new Topic(server);
	_commands["USER"] = new User(server);
	_commands["WHO"] = new Who(server);
}

void CommandHandler::Handler(Client* client, std::vector<std::string> arg, \
							 std::string cmd)
{
	std::map<std::string, Command*>::iterator it = _commands.find(cmd);
	if (it == _commands.end())
		throw ReplyException(ERR_UNKNOWNCOMMAND(cmd));
	else
		_commands[cmd]->implement(client, arg);
}
