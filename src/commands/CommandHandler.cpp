#include "../include/CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server) : _server(server)
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
	_commands["USERCMD"] = new UserCmd(server);
	_commands["WHO"] = new Who(server);

}

void CommandHandler::Handler(Client* client, std::vector<std::string> arg, std::string cmd)
{
	_commands[cmd]->implement(client, arg);
}
