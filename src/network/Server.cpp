/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:34:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 20:41:58 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "DAL.hpp"
#include "Connection.hpp"
#include "defines.hpp"
#include "utils.hpp"

Server::Server(unsigned short port, DAL* data): \
	_port(port), _rqueue(data->getRequestDataContainer()), _data(data)
{
	pollfd	servfd;

	_server_fd = newSocket();
	servfd.fd = _server_fd;
	servfd.events = POLLIN;
	servfd.revents = 0;
	_pollfds.push_back(servfd);
}

Server::~Server(void)
{
	for (pollfds_iterator_t it = _pollfds.begin(); it != _pollfds.end(); it++)
		close(it->fd);
	for (connection_iterator_t it = _connections.begin(); it != _connections.end(); it++)
		delete it->second;
}

void	Server::handlePollEvents(void)
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

void	Server::onClientDisconnect(pollfd& fd)
{
	connection_iterator_t	it = _connections.find(fd.fd);

	if (it != _connections.end())
	{
		Connection	*c = _connections.find(fd.fd)->second;
		char		log_message[NI_MAXHOST + 1024];

		_connections.erase(fd.fd);
		sprintf(log_message, "%s:%d disconnected to the server.", \
			c->getHostname().c_str(), c->getPort());
		log(log_message);
		delete c;
	}
}

void	Server::onClientRequest(pollfd& fd)
{
	bool		is_closed = false;
	RequestData	cont;
	std::string	input;

	input = readMessage(fd.fd, is_closed);
	if (is_closed == true)
		fd.revents = POLLHUP;
	else
	{
		cont.who = _connections[fd.fd];
		cont.what = input;
		_rqueue.push(cont);
	}
}

void	Server::onClientConnect(void)
{
	int			fd;
	SA_IN		sa;
	socklen_t	sa_len;
	char		hostname[NI_MAXHOST];
	char		log_message[NI_MAXHOST + 1024];
	Connection	*c;

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
	c = new Connection(fd, hostname, ntohs(sa.sin_port));
	_connections[fd] = c;
	_data->newClient(c);
	sprintf(log_message, "%s:%d connected to the server.", \
		c->getHostname().c_str(), c->getPort());
	log(log_message);
}

std::string	Server::readMessage(int fd, bool& is_closed)
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
	SA_IN	serv_addr = {};
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

void	Server::reply(const Connection* to, std::string const & message) const
{
	send(to->getFd(), message.c_str(), message.length(), 0);
}

void	Server::broadcast(Connection* sender, std::string const & message) const
{
	for (size_t i = 1; i < _pollfds.size(); i++)
	{
		if (_pollfds[i].fd != sender->getFd())
			send(_pollfds[i].fd, message.c_str(), message.length(), 0);
	}
	std::cout << message;
}
