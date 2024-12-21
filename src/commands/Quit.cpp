#include "../include/Command.hpp"
//with Karen
Quit::Quit(Server* server): Command(server)
{
}

Quit::~Quit()
{
}

void Quit::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	// std::string reason;
	// if (arg[0][0] == ":")
	// 	reason = arg[0].substr(1);
	// else
	// 	reason = "quit with no reason";
	//h
}
