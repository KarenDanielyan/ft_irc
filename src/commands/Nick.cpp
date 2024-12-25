#include "Command.hpp"
//done
Nick::Nick(Server* server): Command(server)
{
}

Nick::~Nick()
{
}

void Nickimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.empty() || arg[0].empty())
	{
		throw ReplyException(ERR_NONICKNAMEGIVEN("NICK"));
		return ;
	}
	std::string nickname = arg[0];

	Client *new_client = application->getClient(nickname);
	if (new_client && new_client != client)
	{
		throw ReplyException(ERR_NICKNAMEINUSE(nickname));
		return;
	}
	// application->setClient(client); .....
	client->setNickname(nickname);
}
