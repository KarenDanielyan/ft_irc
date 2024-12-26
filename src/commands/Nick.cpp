#include "Command.hpp"
//done
Nick::Nick()
{
}

Nick::~Nick()
{
}

// void NICK::validate(Client *client,  std::vector<std::string> arg) // arg should be changed to IRCMessage
// {
// 	std::string nickname = message.parameters[0];
// 	if (nickname.empty()) {
// 		throw ReplyException(ERR_NONICKNAMEGIVEN("NICK"));
// 	}

// 	const std::string disallowedChars = " ,*?!@";
// 	if (nickname.find_first_of(disallowedChars) != std::string::npos)
// 		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

// 	const std::string disallowedStartChars = "$:";
// 	const std::string channelPrefixes = "#&+!";
// 	if (disallowedStartChars.find(nickname[0]) != std::string::npos ||
// 		channelPrefixes.find(nickname[0]) != std::string::npos)
// 		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

// 	if (nickname.find('.') != std::string::npos)
// 		throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));

// 	for (size_t i = 0; i < nickname.length(); ++i)
// 	{
// 		if (!isalnum(nickname[i]) &&
// 			nickname[i] != '[' && nickname[i] != ']' &&
// 			nickname[i] != '{' && nickname[i] != '}' &&
// 			nickname[i] != '\\' && nickname[i] != '|')
// 			throw ReplyException(ERR_ERRONEUSNICKNAME(nickname));
// 	}
// }



void Nick::implement(Client *client, ITransport* server, DAL* data, \
			IRCMessage message)
{
	(void)server;
	if (message._parameters.empty() || message._parameters[0].empty())
	{
		throw ReplyException(ERR_NONICKNAMEGIVEN(message._source, "NICK"));
		return ;
	}
	std::string nickname = message._parameters[0];

	Client *new_client = data->getClient(nickname);
	if (new_client && new_client != client)
	{
		throw ReplyException(ERR_NICKNAMEINUSE(message._source, nickname));
		return;
	}
	client->setNickname(nickname);
}
