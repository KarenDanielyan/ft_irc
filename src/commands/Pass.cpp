#include "Command.hpp"
//done
Pass::Pass(Server* server): Command(server)
{
}

Pass::~Pass()
{
}

void Passimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
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
	if (getPassword() != arg[0])
	{
		throw ReplyException(ERR_PASSWDMISMATCH(client->getNickname()));
		return ;
	}
	client->setState(LOGIN);
}

