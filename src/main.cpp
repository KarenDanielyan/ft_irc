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
#include <stdexcept>
#include "Application.hpp"

int	main(int ac, char **av)
{
	Application*	app;

	if (ac != 3)
		std::cout << USAGE_MSG << std::endl;
	else
	{
		try
		{
			app = Application::getInstance(av[1], av[2]);
			app->run();
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	Application::destroyInstance();
	return (0);
}
