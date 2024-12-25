#include "Command.hpp"

//  <target> [<modestring> [<mode arguments>...]]

Mode::Mode()
{ 
}

Mode::~Mode()
{
}

void Mode::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	(void)server;
	if (message._parameters.size() < 2 || message._parameters[0].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("MODE"));
		return;
	}
	std::string target = message._parameters[0].substr(1);
	std::string mode_str = message._parameters[1];
	std::string mode_arg = message._parameters[2];
	Channel* channel = data->getChannel(target);
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("MODE"));
		return ;
	}
	int i = 0;
	while (mode_str[++i])
	{
		bool plus = (mode_str[i++] == '+');
		switch (mode_str[i])
		{
			case 'i':
				channel->setOnlyInvite(plus);
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), \
					channel->getName(), (plus ? "+i" : "-i")));
				break;
			case 't':
				channel->setTopic(plus ? mode_arg : "");
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), \
					channel->getName(), (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel->setPassword(plus ? mode_arg : "");
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), \
					channel->getName(), (plus ? "+k" : "-k")));
				break;
			case 'o':
				if (target != client->getNickname())
				{
					throw ReplyException(ERR_USERSDONTMATCH());
					return;
				}
				if (plus)
					channel->addOperator(client);
				else
					channel->removeOperator(client);
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), \
					channel->getName(), (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel->setLimit(plus ? std::stol(mode_arg) : 0);
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), \
					channel->getName(), (plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
