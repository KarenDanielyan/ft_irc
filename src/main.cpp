/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:51:28 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/25 13:56:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

int	main(int ac, char **av)
{
	Server*	serv;

	if (ac != 3)
		std::cout << USAGE_MSG << std::endl;
	else
	{
		serv = Server::getInstance(av[1], av[2]);
		try
		{
			serv->start();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	Server::destroyInstance();
	return (0);
}
