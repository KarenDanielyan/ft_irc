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
# include "Client.hpp"

class	Server
{
private:
	int				_server_fd;
	unsigned short	_port;

	const std::string	_passwd;

	std::vector<pollfd>		_pollfds;
	std::map<int, Client*>	_clients;


	std::string	readMessage(int fd, bool &is_closed);

	int	newSocket(void);

	void	onClientConnect(void);
	void	onClientDisconnect(pollfd& fd);
	void	onClientRequest(pollfd&fd);
public:
	typedef std::vector<pollfd>::iterator		pollfds_iterator_t;
	typedef std::map<int, Client*>::iterator	clients_iterator_t;

	Server(std::string const & port, std::string const & password);
	~Server();


	void	start(void);
	
	void	reply(int rcode);

	void	send(Client* to, std::string const & message);
};

#endif
