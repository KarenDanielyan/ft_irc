/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:31:10 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/22 23:08:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <stdexcept>
# include <cstdlib>
# include <cstring>
# include <vector>

# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

# include <sys/socket.h>
# include <sys/poll.h>
# include <sys/types.h>

# include <arpa/inet.h>

# include "defines.hpp"

class	Server
{
private:
	static Server*	_instance;

	bool			_running;
	int				_server_fd;
	unsigned short	_port;

	const std::string	_passwd;

	std::vector<pollfd>	_pollfds;


	Server(std::string const & port, std::string const & password);
	~Server();
public:
	typedef std::vector<pollfd>::iterator	pollfds_iterator_t;

	static Server*	getInstance(std::string const & port, \
							std::string const & password);
	static void		destroyInstance(void);

	int		newSocket(void);

	void	start(void);
};

#endif
