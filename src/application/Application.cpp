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
	_serv = new Server(static_cast<unsigned short>(p), _requests);
}

Application::~Application(void)
{
	delete _serv;
	for (channel_iterator_t i = _channels.begin(); i != _channels.end(); i++)
		delete *i;
	for (clients_iterator_t i = _clients.begin(); i != _clients.end(); i++)
		delete i->second;
}

void	Application::destroyInstance(void)
{
	delete _instance;
	_instance = NULL;
}

void	Application::process(void)
{
	while (_requests.size() != 0)
	{
		// TODO: Add Presentation layer and application layer methods.
		std::cout << _requests.front().what;
		_requests.pop();
	}
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
	while(true)
	{
		_serv->handlePollEvents();
		process();
	}
}
