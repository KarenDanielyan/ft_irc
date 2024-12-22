#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "IRCClient.hpp"

class IRCClient;

class Channel
{
	private:
		int _clientLimit;
		std::string _name; // without #
		std::string _topic;
		std::string _password;
		std::vector<IRCClient* > _clients;
		// IRCClient _admin;   idk do we need?
	public:
		Channel(std::string name, std::string topic);
		~Channel();
		/*getters*/
		std::string getName() const;
		std::string getTopic() const;
		std::string getPass() const;
		std::vector<IRCClient*> getClients() const;
        int getClientCount() const;
        int getLimit() const;
		/*setters*/
		void setName(std::string name);
		void setPass(std::string pass);
		void setTopic(std::string topic);

		void addClient(IRCClient *client);
		void removeClient(IRCClient *client);
		bool isExist(IRCClient client);
};

#endif