/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:09:45 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 21:29:34 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>
# include <algorithm>
# include "Client.hpp"
# include "Server.hpp"

class Client;

class Channel
{
private:
	unsigned long			_clientLimit;
	bool					_onlyInvite;
	std::string				_name;
	std::string				_topic;
	std::string				_password;
	std::vector<Client* >	_clients;
	std::vector<Client* >	_inviteList;
	std::vector<Client* >	_operators;
	Client*					_admin;
public:
	Channel(std::string name, std::string topic, \
		std::string pass, Client* admin);
	~Channel();

	/*getters*/
	std::string getName() const;
	std::string getTopic() const;
	std::string getPassword() const;
	std::vector<std::string> getNicknames() const;
	std::vector<Client*> getClients() const;
	int getClientCount() const;
	int getLimit() const;

	/*setters*/
	void setName(std::string name);
	void setPassword(std::string pass);
	void setAdmin(Client* admin);
	void setTopic(std::string topic);
	void setLimit(unsigned long limit);
	void setOnlyInvite(bool OnlyInvite);
	void addOperator(Client *client);
	void setInvite(Client *client);

	void removeClient(Client *client);
	void removeOperator(Client *client);

	void addClient(Client *client);
	bool isExist(Client *client);
	bool isInvited(Client* client);
	bool isOperator(Client* client);
	bool isInviteOnly();
};

#endif
