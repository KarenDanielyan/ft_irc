/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:16:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/30 02:32:47 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Connection.hpp"

Client::Client(const Connection* connection): _state(CONNECT), \
	_channel(NULL), _connection(connection)
{}

std::string const &	Client::getNickname(void) const
{
	return (_nickname);
}

std::string const &	Client::getUsername(void) const
{
	return (_username);
}

std::string const &	Client::getRealname(void) const
{
	return (_realname);
}

const Connection*	Client::getConnection(void) const
{
	return (_connection);
}

const Channel*		Client::getChannel(void) const
{
	return (_channel);
}

void	Client::setNickname(std::string const & nickname)
{
	_nickname = nickname;
}

void	Client::setUsername(std::string const & username)
{
	_username = username;
}

std::string		Client::getSource() const
{
	std::string source = _nickname;
	if (!_username.empty())
		source = source + "!" + _username;
	if (!_connection->getHostname().empty())
		source = source + "@" + _connection->getHostname();
	return source;
}

void	Client::setRealname(std::string const & realname)
{
	_realname = realname;
}

void	Client::setState(Client::ClientState state)
{
	_state = state;
}

void	Client::join(Channel* channel)
{
	_channel = channel;
}

void	Client::part(void)
{
	_channel = NULL;
}

Client::~Client(void) {}


Client::ClientState const &	Client::getState(void) const
{
	return _state;
}