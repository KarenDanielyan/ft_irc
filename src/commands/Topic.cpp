#include "../include/Command.hpp"
// doning
Topic::Topic(Server* server): Command(server)
{
}

Topic::~Topic()
{
}

void Topic::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	if (arg.size() < 1)
	{
		throw ReplyException(ERR_NEEDMOREPARAMS("TOPIC"));
		return ;
	}
	std::string channel = arg[0];
	// Channel* channel = ----.getChannel();
	if (channel.empty() || channel[0] != '#')
	{
		throw ReplyException(ERR_NOSUCHCHANNEL("TOPIC"));
		return ;
	}
	std::vector<std::string> nicknames;
	nicknames.push_back("marihovh");
	nicknames.push_back("somurady");
	nicknames.push_back("liaydiny");
	nicknames.push_back("amidoyan");

	// std::vector<std::string> nicknames = channel.getNicknames();
	std::vector<std::string>::iterator	i;
		
	for (i = nicknames.begin(); i != nicknames.end(); i++)
		if (*i == client->getNickname())
			break;
	if (i == nicknames.end())
	{
		throw ReplyException(ERR_NOTONCHANNEL(client->getNickname()));
		return ;
	}
	//check for permisions of operator
	if (arg[1])
		channel.setTopic(arg[1]);
	else
		std::cout << channel << std::endl;
		// print somehow the getTopic
}
