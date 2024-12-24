/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:16:22 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 20:33:00 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(int fd, char *hostname, unsigned short port): \
	_fd(fd), _hostname(hostname), _port(port) {}

Connection::~Connection(void) {}

std::string const & Connection::getHostname(void) const
{
	return (_hostname);
}

unsigned short Connection::getPort(void) const
{
	return (_port);
}

int	Connection::getFd(void) const
{
	return (_fd);
}
