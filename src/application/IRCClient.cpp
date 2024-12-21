/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:16:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/21 14:44:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include "Client.hpp"

IRCClient::IRCClient(int fd, char *hostname, unsigned short port): \
	Client(fd, hostname, port) {}

IRCClient::~IRCClient(void) {}
