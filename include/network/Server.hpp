/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:31:10 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 04:28:00 by kdaniely         ###   ########.fr       */
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
# include <queue>

# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <netdb.h>

# include <sys/socket.h>
# include <sys/poll.h>
# include <sys/types.h>

# include <arpa/inet.h>

# include "ITransport.hpp"
# include "defines.hpp"

class	DAL;

struct	RequestData
{
	Client*	who;
	std::string	what;
};

class	Server: public ITransport
{
public:
	typedef std::vector<pollfd>::iterator			pollfds_iterator_t;
	typedef std::map<int, Connection*>::iterator	connection_iterator_t;
private:
	int									_server_fd;
	unsigned short						_port;

	std::vector<pollfd>					_pollfds;
	std::map<int, Connection*>			_connections;

	request_data_container_t&			_rqueue;
	DAL*								_data;

	std::string	readMessage(int fd, bool &is_closed);

	void	_subscribe(const Connection* connection);
	void	_unsubscribe(const Connection* connection);

	int		newSocket(void);

	void	onClientConnect(void);
	void	onClientDisconnect(pollfd& fd);
	void	onClientRequest(pollfd&fd);
public:
	Server(unsigned short port, DAL* data);
	~Server();

	void	handlePollEvents(void);
	
	void	reply(const Connection* to, std::string const & message) const;
	void	broadcast(Connection* sender, std::string const & message) const;
	void	closeConnection(const Connection* connection);
};

#endif
