#include "../include/Commands.hpp"

Commands::Commands(Server *server) : _server(server)
{
 
}

void Commands::handler(Client* _client, std::vector<std::string> _arg, std::string _cmd)
{
	if (!_cmd.compare("CAP"))
		Cap(_client, _arg);
	else if (!_cmd.compare("WHO"))
		Who(_client, _arg);
	else if (!_cmd.compare("PASS"))
		Pass(_client, _arg);
	else if (!_cmd.compare("JOIN"))
		Join(_client, _arg);
	else if (!_cmd.compare("KICK"))
		Kick(_client, _arg);
	else if (!_cmd.compare("MODE"))
		Mode(_client, _arg);
	else if (!_cmd.compare("QUIT"))
		Quit(_client, _arg);
	else if (!_cmd.compare("NICK"))
		Nick(_client, _arg);
	else if (!_cmd.compare("PONG"))
		Pong(_client, _arg);
	else if (!_cmd.compare("PING"))
		Ping(_client, _arg);
	else if (!_cmd.compare("PART"))
		Part(_client, _arg);
	else if (!_cmd.compare("TOPIC"))
		Topic(_client, _arg);
	else if (!_cmd.compare("NOTICE"))
		Notice(_client, _arg);
	else if (!_cmd.compare("INVITE"))
		Invite(_client, _arg);
	else if (!_cmd.compare("PRIVMSG"))
		PrivMsg(_client, _arg);
	else if (!_cmd.compare("USERCMD")) // also known as user 
		UserCmd(_client, _arg);
	else
		std::cout << "Error: command not found\n" << _arg[0]; 
}
