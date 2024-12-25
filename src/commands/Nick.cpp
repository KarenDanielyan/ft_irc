#include "Command.hpp"
//done
Nick::Nick(Server* server): Command(server)
{
}

Nick::~Nick()
{
}

void Nick::implement(Client* client, std::vector<std::string> arg)
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
