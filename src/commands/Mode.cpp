#include "Command.hpp"

//  <target> [<modestring> [<mode arguments>...]]

Mode::Mode(Server* server): Command(server)
{ 
}

Mode::~Mode()
{
}

void Modeimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.size() < 2 || arg[0].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("MODE"));
		return;
	}
	std::string target = arg[0].substr(1);
	std::string mode_str = arg[1];
	std::string mode_arg = arg[2];
	Channel* channel = aplication.getChannel(target);
	if (!channel->isOperator(*client))
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
	while (arg[1][++i])
	{
		bool plus = (arg[1][i++] == '+');
		switch (arg[1][i])
		{
			case 'i':
				channel->setOnlyInvite(plus);
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), (plus ? "+i" : "-i")));
				break;
			case 't':
				channel->setTopic(plus ? mode_arg : "");
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel->setPassword(plus ? mode_arg : "");
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), (plus ? "+k" : "-k")));
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
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel->setLimit(plus ? std::stol(mode_arg) : 0);
				channel->broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), (plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
