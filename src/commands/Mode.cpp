#include "../include/Command.hpp"

//  <target> [<modestring> [<mode arguments>...]]

Mode::Mode(Server* server): Command(server)
{
}

Mode::~Mode()
{
}

void Mode::implement(IRCClient* client, std::vector<std::string> arg)
{
	if (arg.size() < 2 || arg[0].empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS(client->getNickname() + "MODE"));
		return;
	}
	std::string target = arg[0].substr(1);
	std::string mode_arg = arg[2];
	std::string channel = target.substr(1);
	std::vector<Channel* >::iterator	i;
			
	for (i = channels.begin(); i != channels.end(); i++)
		if (*i == target)
				break;
	if (arg[0] != '#' || i == channels.end())
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(target));
		return ;
	}
	// Channel* channel = ----.getChannel(target);
	int i = 0;
	while (arg[++i])
	{
		// i y k o l
		bool plus = (arg[i++] == '+');
		switch (arg[i])
		{
			case 'i':
				channel.setonlyInvite(plus);
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
				if (plus)
					channel.setOperator(mode_arg);
				else
					chennel.removeOp(mode_arg);
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+o" : "-o")));
				break;
			case 'l':
				channel.setLimit(plus ? std::stol(mode_arg) : 0);
				channel.broadcast(RPL_CHANNELMODEIS(client->getNickname(), channel, (plus ? "+o" : "-o")));
				break;
			default:
				break;
		}
		return ;
	}
}
