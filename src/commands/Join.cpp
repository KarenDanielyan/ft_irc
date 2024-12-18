#include "../include/Command.hpp"

// JOIN <channel>{,<channel>} [<key>{,<key>}]

Join::Join(Server* server): Command(server)
{
}

Join::~Join()
{
}

void Join::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
// 	if (arg.empty())
// 	{
// 		reply->ERR_NEEDMOREPARAMS
// 	}
	
}
