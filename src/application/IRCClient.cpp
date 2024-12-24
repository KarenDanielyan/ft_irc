/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:16:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 16:31:52 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include "Connection.hpp"

IRCClient::IRCClient(int fd, char *hostname, unsigned short port): \
	Connection(fd, hostname, port) {}

IRCClient::~IRCClient(void) {}
