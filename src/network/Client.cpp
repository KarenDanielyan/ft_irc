/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:16:22 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/25 15:51:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, char *hostname, unsigned short port): \
	_fd(fd), _hostname(hostname), _port(port) {}

Client::~Client(void) {}

std::string const & Client::getHostname(void) const
{
	return (_hostname);
}

unsigned short Client::getPort(void) const
{
	return (_port);
}

int	Client::getFd(void) const
{
	return (_fd);
}
