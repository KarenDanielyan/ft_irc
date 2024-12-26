#include "Command.hpp"

//done done
//<target>{,<target>} <text to be sent>

PrivMsg::PrivMsg()
{
}

PrivMsg::~PrivMsg()
{
}

void PrivMsg::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	if (message._parameters.size() < 2 || message._parameters[0].empty() || \
		message._parameters[1].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, \
			client->getNickname() + "PRIVMSG"));
		return;
	}
	std::string target = message._parameters[0];
	std::string msg = "";
	for (unsigned long i = 1; i < message._parameters.size(); i++)
	{
		msg += message._parameters[i];
		msg += " ";
	}
	if (target[0] == '#')
	{
		std::string name = target.substr(1);
		Channel* channel = data->getChannel(name);
		if (!channel)
		{
			throw ReplyException(ERR_NOSUCHCHANNEL(message._source, "PRIVMSG"));
			return ;
		}
		if (!channel->isExist(client))
		{
			throw ReplyException(ERR_CANNOTSENDTOCHAN(message._source, \
				channel->getName()));
			return ;
		}
		channel->broadcast(msg);
		return ;
	}
	Client *dest = data->getClient(target);
	if (!dest)
	{
		throw ReplyException(ERR_NOSUCHNICK(message._source, \
			client->getNickname()));
		return;
	}
	server->reply(dest->getConnection(), (message._source + msg));
}
