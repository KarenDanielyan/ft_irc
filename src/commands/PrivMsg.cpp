#include "Command.hpp"

//done done
//<target>{,<target>} <text to be sent>

PrivMsg::PrivMsg(Server* server): Command(server)
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsgimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
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
		std::string name = target.substr(1);
		Channel* channel = aplication->getChannel(name);
		if (!channel)
		{
			throw ReplyException(ERR_NOSUCHCHANNEL("PRIVMSG"));
			return ;
		}
		if (!channel->isExist(*client))
		{
			throw ReplyException(ERR_CANNOTSENDTOCHAN(channel->getName()));
			return ;
		}
		channel->broadcast(message);
		return ;
	}
	Client *dest = application->getClient(target);
	if (!dest)
	{
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	SendMessage(dest, message);
}
