/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:53:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/21 14:53:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"
#include "utils.hpp"

Application*	Application::_instance = NULL;

Application::Application(std::string const & port, \
				std::string const & password): _password(password)
{
	int	p;

	if (port.find_first_not_of("0123456789") != port.npos)
		throw std::runtime_error(ERR_PNAN);
	p = std::atoi(port.c_str());
	if (p <= 1023 || p >= UINT16_MAX)
		throw std::runtime_error(ERR_PINV);
	_serv = new Server(static_cast<unsigned short>(p));
}

Application::~Application(void)
{
	delete _serv;
}

void	Application::destroyInstance(void)
{
	delete _instance;
	_instance = NULL;
}

Application*	Application::getInstance(std::string const & port, \
								std::string const & password)
{
	if (_instance == NULL)
		_instance = new Application(port, password);
	return (_instance);
}

void	Application::run()
{
	log(INFO_LISTEN);
	while (true)
	{
		_serv->polling();
	}
}
