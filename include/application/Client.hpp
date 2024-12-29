/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 14:32:06 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Client_HPP
# define Client_HPP

# include "Connection.hpp"

class	Channel;

class	Client
{
public:
	enum	ClientState
	{
		CONNECT,
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
	ClientState const &	getState(void) const;

	const Channel*		getChannel(void) const;
	const Connection*	getConnection(void) const;

	void	join(Channel* channel);
	void	part(void);

	void	setNickname(std::string const & nickname);
	void	setUsername(std::string const & username);
	void	setRealname(std::string const & realname);
	void 	setState(Client::ClientState state);
	~Client();
};

#endif
