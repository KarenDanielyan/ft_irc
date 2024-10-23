/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:02:33 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/23 19:12:27 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <string>
# include <netdb.h>

class	Client
{
private:
	int				_fd;
	std::string		_hostname;
	unsigned short	_port;

public:
	Client(int fd, char *hostname, unsigned short port);
	~Client();

	std::string const &	getHostname(void) const;
	unsigned short		getPort(void) const;
};

#endif
