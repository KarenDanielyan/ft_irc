/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:09:45 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/24 20:13:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<<< HEAD:include/Channel.hpp
#ifndef CHANNEL_HPP
# define CHANNEL_HPP
========
#include "IRCClient.hpp"

IRCClient::IRCClient(int fd, char *hostname, unsigned short port): \
	Client(fd, hostname, port)
{

}
>>>>>>>> commands:src/application/IRCClient.cpp

class	Channel
{
private:
	Channel() {}

public:
};

#endif
