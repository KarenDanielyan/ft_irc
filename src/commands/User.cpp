#include "Command.hpp"
//done done
User::User()
{
}

User::~User()
{

}

void User::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
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
	(void)data;
	if (message._parameters.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "USER"));
		return ;
	}
	if (client->getState() == Client::LIVE)
	{
		throw ReplyException(ERR_ALREADYREGISTERED(message._source, \
			client->getUsername()));
		return ;
	}
	client->setUsername(message._parameters[0]);
	client->setRealname(message._parameters[3]);
	server->reply(client->getConnection(), \
		RPL_WELCOME(message._source, client->getUsername()));
}
