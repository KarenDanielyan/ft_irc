#include "Command.hpp"
//done
Pass::Pass(Server* server): Command(server)
{
}

Pass::~Pass()
{
}

void Pass::implement(IRCClient* client, std::vector<std::string> arg)
{
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("PASS"));
		return ;
	}
	if (client->getState() == LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(client->getNickname()));
		return ;
	}
	if (_server->getPassword() != arg[0])
	{
		throw ReplyException(ERR_PASSWDMISMATCH(client->getNickname()));
		return ;
	}
	client->setState(LOGIN);
}

