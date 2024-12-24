/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 17:18:04 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include "Connection.hpp"
# include "Channel.hpp"

class	Client
{
public:
	enum	ClientState
	{
		LOGIN,
		LIVE,
		DISCONNECTED
	};
private:
	std::string			_nickname;
	std::string			_username;
	std::string			_realname;

	ClientState			_state;
	Channel*			_channel;
	const Connection*	_connection;
public:
	Client(const Connection* connection);

	std::string const &	getNickname(void) const;
	std::string const &	getUsername(void) const;
	std::string const &	getRealname(void) const;

	const Channel*		getChannel(void) const;
	const Connection*	getConnection(void) const;

	void	join(Channel* channel);
	void	part(void);

	void	setNickname(std::string const & nickname);
	void	setUsername(std::string const & username);
	void	setRealname(std::string const & realname);
	~Client();
};

#endif
