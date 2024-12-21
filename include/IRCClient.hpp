/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/25 15:14:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include "Client.hpp"
# include "Channel.hpp"

class	IRCClient : public Client
{
private:
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	// Channel		*_channel;
public:
	enum	e_ClientState
	{
		LOGIN,
		LIVE,
		DISCONNECTED
	};
	IRCClient(int fd, char *hostname, unsigned short port);
	std::string getNickname(){
		return this->_nickname;
	}
	void setNickname(std::string nick){ _nickname = nick;}
	~IRCClient() {};
};

#endif
