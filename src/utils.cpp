/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:17:06 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/23 19:15:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>

void	log(std::string const & message)
{
	time_t		epoch;
	struct tm	datetime;
	char		buf[80];

	time(&epoch);
	datetime = *localtime(&epoch);
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &datetime);
	std::cout << "[ " << buf << " ] " << message << std::endl;
}
