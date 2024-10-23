/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:34:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/24 02:22:37 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include <cerrno>
#include <stdexcept>

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

Server::~Server(void)
{
	for (pollfds_iterator_t it = _pollfds.begin(); it != _pollfds.end(); it++)
		close(it->fd);
	for (clients_iterator_t it = _clients.begin(); it != _clients.end(); it++)
		delete it->second;
}

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

	log(INFO_LISTEN);
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
					onClientConnect();
					break;
				}
				onClientRequest(*it);
			}
			if (it->revents & POLLHUP)
			{
				onClientDisconnect(*it);
				_pollfds.erase(it);
				break ;
			}
		}
	}
}

void	Server::onClientDisconnect(pollfd& fd)
{
	clients_iterator_t	it = _clients.find(fd.fd);

	if (it != _clients.end())
	{
		Client	*c = _clients.find(fd.fd)->second;
		char	log_message[NI_MAXHOST + 1024];

		_clients.erase(fd.fd);
		sprintf(log_message, "%s:%d disconnected to the server.", \
			c->getHostname().c_str(), c->getPort());
		log(log_message);
		delete c;
	}
}

void	Server::onClientRequest(pollfd& fd)
{
	bool		is_closed = false;
	std::string	input;

	input = read_message(fd.fd, is_closed);
	if (is_closed == true)
		fd.revents = POLLHUP;
	else
		std::cout << input;
}

void	Server::onClientConnect(void)
{
	int					fd;
	struct sockaddr_in	sa;
	socklen_t			sa_len;
	char				hostname[NI_MAXHOST];
	char				log_message[NI_MAXHOST + 1024];
	Client				*c;

	sa_len = sizeof(sa);
	fd = accept(_server_fd, (SA*)(&sa), &sa_len);
	if (fd < 0)
		throw std::runtime_error(ERR_SCKFAIL);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error(ERR_FNBLCK);
	pollfd	pfd = {fd, POLLIN, 0};
	_pollfds.push_back(pfd);
	if (getnameinfo((SA*)(&sa), sa_len, hostname, NI_MAXHOST, \
					NULL, 0, NI_NUMERICSERV) < 0)
	{
		throw std::runtime_error(ERR_HOSTNAME);
	}
	c = new Client(fd, hostname, ntohs(sa.sin_port));
	_clients[fd] = c;
	sprintf(log_message, "%s:%d connected to the server.", \
		c->getHostname().c_str(), c->getPort());
	log(log_message);
}

std::string	Server::read_message(int fd, bool& is_closed)
{
	std::string	msg;
	char		buffer[BUFFER_SIZE + 1];
	int			rv;

	do
	{
		memset(buffer, 0, BUFFER_SIZE);
		rv = recv(fd, buffer, BUFFER_SIZE, 0);
		buffer[rv] = 0;
		if (rv == 0)
		{
			is_closed = true;
			break;
		}
		else if (rv < 0 && rv != EWOULDBLOCK)
			throw std::runtime_error(strerror(errno));
		msg.append(buffer);
	}
	while (rv == BUFFER_SIZE);
	return (msg);
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
