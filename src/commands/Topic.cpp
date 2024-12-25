#include "Command.hpp"
// done done
Topic::Topic()
{
}

Topic::~Topic()
{
}

void Topic::implement(Client *client, ITransport* server, DataContainer* data, \
			IRCMessage message)
{
	if (message._parameters.size() < 1)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("TOPIC"));
		return ;
	}
	std::string name = message._parameters[0].substr(1);
	Channel* channel = data->getChannel(name);
	if (!channel)
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("TOPIC"));
		return ;
	}
	if (!channel->isExist(client))
	{
		throw ReplyException(ERR_NOTONCHANNEL(client->getNickname()));
		return ;
	}
	if (!channel->isOperator(client))
	{
		throw ReplyException(ERR_CHANOPRIVSNEEDED(client->getNickname()));
		return ;
	}
	if (!message._parameters[1].empty())
		channel->setTopic(message._parameters[1]);
	else
		server->reply(client->getConnection(), channel->getTopic());
}
