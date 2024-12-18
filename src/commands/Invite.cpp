#include "../include/Command.hpp"

//INVITE <nickname> <channel>

Invite::Invite(Server* server): Command(server)
{
}

Invite::~Invite()
{
}

void Invite::implement(IRCClient* client, std::vector<std::string> arg)
{
	(void)client;
	(void)arg;
	// if (_arg.size() < 2)
	// {
	// 	// error_msg NEEDMOREPARAMS
	// }

	// IRCClient* _IRCClientToInvite = _server->getUser(_arg[0]);
	// Channel* _channelToInvite = _server->getChannel(_arg[1]);

	// if (!_IRCClientToInvite)
	// {
	// 	//error_msg ERR_NOSUCHNICK
	// }
	// if (!_channelToInvite)
	// {
	// 	//error_msg ERR_NOSUCHCHANNEL
	// }
	// if (_ch)
	// check if the _IRCClient is in channel
	// check if the _IRCClient has the permision to invite
	// 
}
