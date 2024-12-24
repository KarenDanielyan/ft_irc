/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:16:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 17:06:54 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Connection.hpp"

Client::Client(int fd, char *hostname, unsigned short port): \
	Connection(fd, hostname, port) {}

Client::~Client(void) {}
