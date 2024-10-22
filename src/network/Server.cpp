/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:34:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/16 23:38:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "defines.hpp"
#include <cerrno>
#include <stdexcept>
#include <sys/poll.h>

Server*	Server::_instance = NULL;

Server::Server(std::string const & port, std::string const & password): \
	_running(true), _passwd(password)
{
	int	p;

	if (port.find_first_not_of("0123456789") != port.npos)
		throw std::runtime_error(ERR_PNAN);
	p = std::atoi(port.c_str());
	if (p <= 1023 || p >= UINT16_MAX)
		throw std::runtime_error(ERR_PINV);
	_port = static_cast<unsigned short>(p);
	_server_fd = newSocket();
}

Server::~Server(void) {}

Server*	Server::getInstance(std::string const & port, std::string const & password)
{
	if (_instance == NULL)
		_instance = new Server(port, password);
	return (_instance);
}

void	Server::destroyInstance(void)
{
	if (_instance != NULL)
	{
		delete _instance;
		_instance = NULL;
	}
}

void	Server::start(void)
{
	pollfd	servfd = {_server_fd, POLLIN, 0};

	_pollfds.push_back(servfd);

	std::cout << "Server listens to any new connections..." << std::endl;
	while (_running)
	{
		if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 1)
			throw std::runtime_error(ERR_POLL);
		for (pollfds_iterator_t it = _pollfds.begin(); it != _pollfds.end(); it++)
		{
			if (it->revents == 0)
				continue ;
			if (it->revents & POLLIN)
			{
				/* If new client connects */
				if (it->fd == _server_fd)
				{
					std::cout << "A new client tries to connect" << std::endl;
					close(accept(it->fd, NULL, NULL));
					break ;
				}
				std::cout << "Anyways" << std::endl;
			}
		}
	}
}

int	Server::newSocket()
{
	int	sockfd;

	try
	{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error(ERR_SCKFAIL);
	/* Setting the socket into non-blocking mode. */
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error(ERR_FNBLCK);
	int	val = -42;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0)
		throw std::runtime_error(ERR_FBIND);

	/* Naming the socket */
	struct sockaddr_in	serv_addr = {};
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(_port);

	if (bind(sockfd, (const SA*)(&serv_addr), sizeof(serv_addr)) < 0)
		throw std::runtime_error(ERR_ADDRBIND);
	/* Making socket to listen to requests */
	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error(ERR_CREFUSED);
	}
	catch (std::exception	&e)
	{
		if (sockfd >= 0)
			close(sockfd);
		throw e;
	}
	return (sockfd);
}

