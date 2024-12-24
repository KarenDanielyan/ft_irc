#include "Command.hpp"

//  <target> [<modestring> [<mode arguments>...]]

Mode::Mode(Server* server): Command(server)
{ 
}

Mode::~Mode()
{
}

void Mode::implement(Client* client, std::vector<std::string> arg)
{
	if (arg.size() < 2 || arg[0].empty())
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("MODE"));
		return;
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	std::string target = arg[0].substr(1);
	std::string mode_str = arg[1];
	std::string mode_arg = arg[2];
	Channel* channel = aplication.getChannel(target);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("MODE"));
		return ;
	}
	int i = 0;
	while (arg[1][++i])
	{
		bool plus = (arg[i++] == '+');
		switch (arg[i])
		{
			case 'i':
				channel.setOnlyInvite(plus);
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+i" : "-i")));
				break;
			case 't':
				channel.setTopic(plus ? mode_arg : "");
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+t" : "-t")));
				break;
			case 'k':
				channel.setPassword(plus ? mode_arg : "");
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+k" : "-k")));
				break;
			case 'o':
				Client operator = channel->isExist(mode_arg);
				if (!operator)
				{
					throw ReplyException(ERR_NOSUCHNICK(mode_arg));
					return;
				}
				if (plus)
					channel.addOperator(operator);
				else
					chennel.removeOperator(operator);
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel.setLimit(plus ? std::stol(mode_arg) : 0);
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+l" : "-l")));
				break;
			default:
				break;
		}
		return ;
	}
}
