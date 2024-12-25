#include "Command.hpp"
//done done
User::User(Server* server): Command(server)
{
}

User::~User()
{

}


void User::validate(Client *client, std::vector<std::string> arg) // arg neeed to be changed to IRCSMessage
{
	if ( message._parametrs.size() < 4)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return ;
	}

	std::string username = message._parameters[0];
	std::string param2 = message._parameters[1];
	std::string param3 = message._parameters[2];
	std::string realname = message._parameters[3];
	if (username.empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return ; //// ??????
	}
	if (param2 != "0" || param3 != "*")
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return;
	}
	else if (realname.empty() || realname[0] != ':')
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("USER"));
		return;
	}

	// last paramter should be the realname
	// what is meaningfull???
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
