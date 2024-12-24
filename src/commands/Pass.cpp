#include "../include/Command.hpp"
//done
Pass::Pass(Server* server): Command(server)
{
}

Pass::~Pass()
{
}

void Pass::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	if (arg.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("Pass"));
		return ;
	}
	// if (client->isRegistered())
	// {
	// 	throw ReplyException(ERR_ALREADYREGISTERED("alabula"));
	// 	return ;
	// }
	// if (_server->getPassword() != arg[0])
	// {
	// 	throw ReplyException(ERR_PASSWDMISMATCH(" "));
	// 	return ;
	// }
}

