#include "Command.hpp"

//  <target> [<modestring> [<mode arguments>...]]

Mode::Mode()
{ 
}

Mode::~Mode()
{
}

void Mode::implement(Client *client, ITransport* server, DAL* data, \
			IRCMessage message)
{
	(void)server;
	if (message._parameters.size() < 2 || message._parameters[0].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "MODE"));
		return;
	}
	std::string target = message._parameters[0].substr(1);
	std::string mode_str = message._parameters[1];
	std::string mode_arg = message._parameters[2];
	Channel* channel = data->getChannel(target);
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message._source, \
			client->getNickname()));
		return ;
	}
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message._source, "MODE"));
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
				broadcast(server, channel, RPL_CHANNELMODEIS(message._source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+i" : "-i")));
				break;
			case 't':
				channel->setTopic(plus ? mode_arg : "");
				broadcast(server, channel, RPL_CHANNELMODEIS(message._source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel->setPassword(plus ? mode_arg : "");
				broadcast(server, channel, RPL_CHANNELMODEIS(message._source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+k" : "-k")));
				break;
			case 'o':
				if (target != client->getNickname())
				{
					throw ReplyException(ERR_USERSDONTMATCH(message._source));
					return;
				}
				if (plus)
					channel->addOperator(client);
				else
					channel->removeOperator(client);
				broadcast(server, channel, RPL_CHANNELMODEIS(message._source, \
					client->getNickname(), \
					channel->getName(), (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel->setLimit(plus ? std::atol(mode_arg.c_str()) : 0);
				broadcast(server, channel, RPL_CHANNELMODEIS(message._source, \
					client->getNickname(), channel->getName(), \
					(plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
