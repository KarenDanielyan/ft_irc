/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:31:10 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 14:59:21 by kdaniely         ###   ########.fr       */
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


struct	RequestData
{
	Connection*	who;
	std::string	what;
};

class	Server: public ITransport
{
public:
	typedef std::queue<RequestData>					RequestDataContainer;
	typedef std::vector<pollfd>::iterator			pollfds_iterator_t;
	typedef std::map<int, Connection*>::iterator	connection_iterator_t;
private:
	int									_server_fd;
	unsigned short						_port;

	std::vector<pollfd>					_pollfds;
	std::map<int, Connection*>			_connections;

	std::queue<RequestData>&	_rqueue;

	std::string	readMessage(int fd, bool &is_closed);

	int	newSocket(void);

	void	onClientConnect(void);
	void	onClientDisconnect(pollfd& fd);
	void	onClientRequest(pollfd&fd);
public:
	Server(unsigned short port, std::queue<RequestData>& rqueue);
	~Server();

	void	handlePollEvents(void);
	
	void	reply(Connection* to, std::string const & message);

	void	broadcast(std::string const & message);

	const RequestData *	hasPendingRequest(void);
};

#endif
