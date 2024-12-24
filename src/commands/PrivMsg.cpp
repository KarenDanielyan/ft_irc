#include "../include/Command.hpp"

//done
//<target>{,<target>} <text to be sent>

PrivMsg::PrivMsg(Server* server): Command(server)
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (arg.size() < 2 || arg[0].empty() || arg[1].empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS(client->getNickname() + "PRIVMSG"));
		return;
	}
	std::string target = arg[0];
	std::string message = "";
	for (unsigned long i = 1; i < arg.size(); i++)
	{
		message += arg[i];
		message += " ";
	}
	if (target[0] == '#')
	{
		std::string channel = target.substr(1);
		// Channel* channel = ----.getChannel();
		if (channel.empty())
		{
			throw ReplyException(ERR_NOSUCHCHANNEL("PRIVMSG"));
			return ;
		}
		// std::vector<std::string> nicknames = channel.getNicknames();
		std::vector<std::string>::iterator	i;
			
		for (i = nicknames.begin(); i != nicknames.end(); i++)
			if (*i == client->getNickname())
				break;
		if (i == nicknames.end())
		{
			throw ReplyException(ERR_CANNOTSENDTOCHAN("channel"));
			return ;
		}
		//channel.broadcast()            need the definition of method
		return ;
	}
	std::string dest = target;
	// Client *dest = _server->getClient(target);
	if (dest.empty()) {
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	std::cout << "To client" +  message << std::endl;
}
