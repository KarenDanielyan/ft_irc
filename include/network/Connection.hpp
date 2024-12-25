/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:02:33 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 16:28:01 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <string>
# include <netdb.h>

/* 
 * NOTE: Never modify this class.
*/

class	Connection
{
protected:
	int				_fd;
	std::string		_hostname;
	unsigned short	_port;

public:
	Connection(int fd, char *hostname, unsigned short port);
	virtual ~Connection();

	std::string const &	getHostname(void) const;
	unsigned short		getPort(void) const;
	int					getFd(void) const;
};

#endif
