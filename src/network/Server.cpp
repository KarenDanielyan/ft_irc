/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:34:59 by kdaniely          #+#    #+#             */
/*   Updated: 2025/01/02 20:05:01 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
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
		throw RuntimeException(ERR_POLL);
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
				break ;
			}
			onClientRequest(*it);
		}
		if (it->revents & POLLHUP)
		{
			onClientDisconnect(*it);
			break ;
		}
	}
}

void	Server::closeConnection(const Connection* connection)
{
	char		log_message[NI_MAXHOST + 1024];

	_connections.erase(connection->getFd());
	snprintf(log_message,sizeof(log_message), "%s:%d disconnected to the server.", \
		connection->getHostname().c_str(), connection->getPort());
	log(log_message);
	_unsubscribe(connection);
	close(connection->getFd());
	delete connection;
}

/**
 * @brief	_subscribe() adds the connetion to the polling list,
 * 			if it's not present. Otherwise, it will do nothing.
 * 
 * @param connection	The connecion to be added into the polling list.
 */
void	Server::_subscribe(const Connection* connection)
{
	pollfd				pfd = {connection->getFd(), POLLIN, 0};
	pollfds_iterator_t	it;

	for (it = _pollfds.begin(); it != _pollfds.end(); it++)
	{
		if (it->fd == connection->getFd())
			return ;
	}
	if (it == _pollfds.end())
		_pollfds.push_back(pfd);
}

/**
 * @brief	_unsubscribe() removes the connection from the polling list,
 * 			if it's present. Otherwise, it will do nothing.
 * 
 * @param connection	connetion to be removed from the polling list.
 */
void	Server::_unsubscribe(const Connection* connection)
{
	for (pollfds_iterator_t it = _pollfds.begin(); it != _pollfds.end(); it++)
	{
		if (it->fd == connection->getFd())
		{
			_pollfds.erase(it);
			break ;
		}
	}
}

void	Server::onClientDisconnect(pollfd& fd)
{
	connection_iterator_t	it = _connections.find(fd.fd);

	if (it != _connections.end())
		closeConnection(it->second);
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
		cont.who = _data->findClient(fd.fd);
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
		throw RuntimeException(ERR_SCKFAIL);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw RuntimeException(ERR_FNBLCK);
	if (getnameinfo((SA*)(&sa), sa_len, hostname, NI_MAXHOST, \
					NULL, 0, NI_NUMERICSERV) < 0)
	{
		throw RuntimeException(ERR_HOSTNAME);
	}
	c = new Connection(fd, hostname, ntohs(sa.sin_port));
	_subscribe(c);
	_connections[fd] = c;
	_data->newClient(c);
	snprintf(log_message, sizeof(log_message), "%s:%d connected to the server.", \
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
		if (rv == 0)
		{
			is_closed = true;
			break;
		}
		else if (rv < 0)
		{
			if (errno != EWOULDBLOCK)
				throw RuntimeException(strerror(errno));
		}
		else
		{
			buffer[rv] = 0;
			msg.append(buffer);
		}
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
		throw RuntimeException(ERR_SCKFAIL);
	/* Setting the socket into non-blocking mode. */
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
		throw RuntimeException(ERR_FNBLCK);
	int	val = -42;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0)
		throw RuntimeException(ERR_FBIND);

	/* Naming the socket */
	SA_IN	serv_addr = {};
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(_port);

	if (bind(sockfd, (const SA*)(&serv_addr), sizeof(serv_addr)) < 0)
		throw RuntimeException(ERR_ADDRBIND);
	/* Making socket to listen to requests */
	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw RuntimeException(ERR_CREFUSED);
	}
	catch (std::exception	&e)
	{
		if (sockfd >= 0)
			close(sockfd);
		throw RuntimeException(e.what());
	}
	return (sockfd);
}

void	Server::reply(const Connection* to, std::string const & message) const
{
	std::string	packet = message + CRLF;

	std::cout << packet;
	send(to->getFd(), packet.c_str(), packet.length(), 0);
}

void	Server::broadcast(Connection* sender, std::string const & message) const
{
	for (size_t i = 1; i < _pollfds.size(); i++)
	{
	  std::string	packet = message + CRLF;
		if (_pollfds[i].fd != sender->getFd())
			send(_pollfds[i].fd, packet.c_str(), packet.length(), 0);
	}
	std::cout << message;
}
