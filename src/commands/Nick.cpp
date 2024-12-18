#include "../include/Command.hpp"

Nick::Nick(Server* server): Command(server)
{
}

Nick::~Nick()
{
}

void Nick::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	if (arg.empty() || arg[0].empty())
	{
		throw ReplyException(ERR_NONICKNAMEGIVEN("nick"));
		return ;
	}
	// std::string nick = arg[0];
	// if (getclient(nick))
	// {
	// 	throw Reply_Exception(ERR_NICKNAMEINUSE("nick"));
	// }
	// client->setNickname(nick);
}
