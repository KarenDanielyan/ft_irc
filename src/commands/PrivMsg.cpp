#include "Command.hpp"

//done done
//<target>{,<target>} <text to be sent>

PrivMsg::PrivMsg(Server* server): Command(server)
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(Client* client, std::vector<std::string> arg)
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
		if (!channel.isExist(target))
		{
			throw ReplyException(ERR_CANNOTSENDTOCHAN(channel->getNmae()));
			return ;
		}
		channel.broadcast(message);
		return ;
	}
	Client *dest = _server->getClient(target);
	if (!dest) {
		throw ReplyException(ERR_NOSUCHNICK(client->getNickname()));
		return;
	}
	SendMessage(dest, message);
}
