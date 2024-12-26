#include "Command.hpp"
// done done
Topic::Topic()
{
}

Topic::~Topic()
{
}

void Topic::implement(Client *client, ITransport* server, DAL* data, \
			IRCMessage message)
{
	if (message._parameters.size() < 1)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS(message._source, "TOPIC"));
		return ;
	}
	std::string name = message._parameters[0].substr(1);
	Channel* channel = data->getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL(message._source, "TOPIC"));
		return ;
	}
	if (!channel->isExist(client))
	{
		throw ReplyException(ERR_NOTONCHANNEL(message._source, \
			client->getNickname()));
		return ;
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(message._source, \
			client->getNickname()));
		return ;
	}
	if (!message._parameters[1].empty())
		channel->setTopic(message._parameters[1]);
	else
		server->reply(client->getConnection(), \
			(message._source + channel->getTopic()));
}
