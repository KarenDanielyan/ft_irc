#include "Command.hpp"
// done done
Topic::Topic(Server* server): Command(server)
{
}

Topic::~Topic()
{
}

void Topic::implement(Client* client, std::vector<std::string> arg)
{
	if (arg.size() < 1)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("TOPIC"));
		return ;
	}
	std::string name = arg[0][0] == '#' ? arg[0].substr(1) : "";
	Channel* channel = application->getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("TOPIC"));
		return ;
	}
	if (!channel.isExist(client))
	{
		throw ReplyException(ERR_NOTONCHANNEL(client->getNickname()));
		return ;
	}
	if (!client->getOpPerm())
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client));
		return ;
	}
	if (arg[1])
		channel->setTopic(arg[1]);
	else
		SendMessage(client, channel->getTopic());
}
