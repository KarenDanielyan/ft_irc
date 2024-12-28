#include "Command.hpp"
// done done
Topic::Topic() {}

Topic::~Topic() {}

void Topic::implement(Client *client, const ITransport* server, DAL& data, \
			IRCMessage message)
{
	if (message.parameters.size() < 1)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message.source, "TOPIC"));
		return ;
	}
	std::string name = message.parameters[0].substr(1);
	Channel* channel = data.getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message.source, "TOPIC"));
		return ;
	}
	if (!channel->isExist(client))
	{
		throw ReplyException(ERR_NOTONCHANNEL(message.source, \
			client->getNickname()));
		return ;
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message.source, \
			client->getNickname()));
		return ;
	}
	if (!message.parameters[1].empty())
		channel->setTopic(message.parameters[1]);
	else
		server->reply(client->getConnection(), \
			(message.source + channel->getTopic()));
}
