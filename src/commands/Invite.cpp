#include "../include/Command.hpp"

Invite::Invite(Server* server): Command(server)
{
}

Invite::~Invite()
{
}

void Invite::implement(Client* _client, std::vector<std::string> _arg)
{
	(void)_client;
	(void)_arg;
	// if (_arg.size() < 2)
	// {
	// 	// error_msg NEEDMOREPARAMS
	// }

	// Client* _clientToInvite = _server->getUser(_arg[0]);
	// Channel* _channelToInvite = _server->getChannel(_arg[1]);

	// if (!_clientToInvite)
	// {
	// 	//error_msg ERR_NOSUCHNICK
	// }
	// if (!_channelToInvite)
	// {
	// 	//error_msg ERR_NOSUCHCHANNEL
	// }
	// check if the _client is in channel
	// check if the _client has the permision to invite
	// 
}
