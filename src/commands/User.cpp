#include "Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{

}

void User::validate(Client *client, const IRCSMessage &message)
{
	if (message._parameters.size() < 4)
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));

	std::string username = message._parameters[0];
	std::string realname = message._parameters[3];
	std::string param2 = message._parameters[1];
	std::string param3 = message._parameters[2];

	if (param2 != "0" || param3 != "*")
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
	if (username.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
	while (!username.empty() && username[0] == ' ')
		username.erase(0, 1);

	if (!realname.empty() && realname[0] == ':')
		realname.erase(0, 1);

	// client->setUsername(username);
	// client->setRealname(realname); Mar jan sranq en valid username & realname
}

void User::implement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return ;
	}
	if (client->getState() == LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(client->getUsername()));
		return ;
	}
	client->setUsername(arg[0]);
	client->setRealname(arg[3]);
	SendMessage(client, RPL_WELCOME(client->getUsername()));
}
