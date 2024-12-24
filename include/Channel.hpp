#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "IRCClient.hpp"

class IRCClient;

class Channel
{
	private:
		unsigned long _clientLimit;
		bool _onlyInvite;
		std::string _name; // without #
		std::string _topic;
		std::string _password;
		std::vector<IRCClient* > _clients;
		std::vector<IRCClient* > _operators;
	public:
		Channel(std::string name, std::string topic);
		~Channel();
		/*getters*/
		std::string getName() const;
		std::string getTopic() const;
		std::string getPass() const;
		std::vector<std::string> getNicknames() const;
		std::vector<IRCClient*> getClients() const;
        int getClientCount() const;
        int getLimit() const;

		/*setters*/
		void setName(std::string name);
		void setPass(std::string pass);
		void setTopic(std::string topic);
		void setLimit(unsigned long limit);
		void setOnlyInvite(bool OnlyInvite);
		void addOperator(IRCClient *client);


		void removeClient(IRCClient *client);
		void addClient(IRCClient *client);
		void removeClient(IRCClient *client);
		bool isExist(IRCClient client);
		bool isOperator(IRCClient client);
		void broadcast() const;
};

#endif