#include "../include/Command.hpp"

//<channel>{,<channel>} [<reason>]
Part::Part(Server* server): Command(server)
{
}

Part::~Part()
{
}

void Part::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;

	if (arguments.empty()) {
		throw ReplyException(ERR_NEEDMOREPARAMS("PART"));
		return;
	}
	
	std::string name = arg[0];

	
	Channel *channel = _server->getChannel(name);
	if (!channel) {
		throw ReplyException(ERR_NOSUCHCHANNEL(name));
		return;
	}

	if (!client->getChannel() || client->getChannel()->getName() != name) {
		throw ReplyException(ERR_NOTONCHANNEL(client->getNickname));
		return;
	}

	// print for client leave channel "#twilight_zone"
	//channel remove client
}
