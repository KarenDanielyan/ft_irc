/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 16:31:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include "Connection.hpp"
# include "Channel.hpp"

class	IRCClient : public Connection
{
private:
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	Channel		*_channel;
public:
	enum	e_ClientState
	{
		LOGIN,
		LIVE,
		DISCONNECTED
	};
	IRCClient(int fd, char *hostname, unsigned short port);

	~IRCClient();
};

#endif
