/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:31:10 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/23 17:49:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <stdexcept>
# include <cstdlib>
# include <cstring>
# include <cstdio>
# include <vector>
# include <map>

# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <netdb.h>

# include <sys/socket.h>
# include <sys/poll.h>
# include <sys/types.h>

# include <arpa/inet.h>

# include "defines.hpp"
# include "Connection.hpp"

class	ITransport
{
public:
	virtual void	reply(Connection* to, std::string const & message) = 0;
	virtual void	broadcast(std::string const & message) = 0;

	virtual ~ITransport() {}
};

class	Server: public ITransport
{
private:
	int				_server_fd;
	unsigned short	_port;

	std::vector<pollfd>			_pollfds;
	std::map<int, Connection*>	_connections;


	std::string	readMessage(int fd, bool &is_closed);

	int	newSocket(void);

	void	onClientConnect(void);
	void	onClientDisconnect(pollfd& fd);
	void	onClientRequest(pollfd&fd);
public:
	typedef std::vector<pollfd>::iterator			pollfds_iterator_t;
	typedef std::map<int, Connection*>::iterator	clients_iterator_t;

	Server(unsigned short port);
	~Server();

	void	start(void);
	
	void	reply(Connection* to, std::string const & message);

	void	broadcast(std::string const & message);
};

#endif
