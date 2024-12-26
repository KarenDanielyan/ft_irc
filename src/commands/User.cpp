#include "Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{

}

void User::validate(Client *client, IRCSMessage message)
{
	if (message._parameters.size() < 4)
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));

	std::string username = message._parameters[0];
	std::string param2 = message._parameters[1];
	std::string param3 = message._parameters[2];
	std::string realname = message._parameters[3];

	if (username.empty())
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));


	if (!username.empty() && username[0] == ' ')
		username.erase(0, 1);

	std::string user;
	if (!username.empty())
	{
		size_t space_pos = msg.find(' ');
		user = username.substr(0, space_pos != std::string::npos ? space_pos : username.size());
	}
	username = user;
	if (param2 != "0" || param3 != "*")
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));

	if (realname.empty())
		realname = "";

	size_t start_pos = 0;
	for (int i = 0; i < 3; ++i)
	{
		start_pos = realname.find(' ', start_pos + 1);
		if (start_pos == std::string::npos)
			realname = "";
	}

	std::string real = realname.substr(start_pos + 1);
	if (!real.empty() && real[0] == ':')
		real.erase(0, 1); // Remove the colon

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
