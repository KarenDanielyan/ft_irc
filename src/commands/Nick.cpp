#include "Command.hpp"
//done
Nick::Nick(Server* server): Command(server)
{
}

Nick::~Nick()
{
}

void NICK::validate(Client *client,  std::vector<std::string> arg) // arg should be changed to IRCMessage
{
	std::string nickname = message.parameters[0];
	if (nickname.empty()) {
		throw ReplyException(ERR_NONICKNAMEGIVEN("NICK"));
	}

	const std::string disallowedChars = " ,*?!@";
	if (nickname.find_first_of(disallowedChars) != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

	const std::string disallowedStartChars = "$:";
	const std::string channelPrefixes = "#&+!";
	if (disallowedStartChars.find(nickname[0]) != std::string::npos ||
		channelPrefixes.find(nickname[0]) != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

	if (nickname.find('.') != std::string::npos)
		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

	for (size_t i = 0; i < nickname.length(); ++i)
	{
		if (!isalnum(nickname[i]) &&
			nickname[i] != '[' && nickname[i] != ']' &&
			nickname[i] != '{' && nickname[i] != '}' &&
			nickname[i] != '\\' && nickname[i] != '|')
			throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));
	}
}



void Nickimplement(Client *client, std::vector<std::string> arg ,ITransport* server, \
				std::map<int, Client*>& _clients, std::vector<Channel *>& _channels)
{
	if (arg.empty() || arg[0].empty())
	{
		throw ReplyException(ERR_NONICKNAMEGIVEN("NICK"));
		return ;
	}
	std::string nickname = arg[0];

	Client *new_client = application->getClient(nickname);
	if (new_client && new_client != client)
	{
		throw ReplyException(ERR_NICKNAMEINUSE(nickname));
		return;
	}
	// application->setClient(client); .....
	client->setNickname(nickname);
}
