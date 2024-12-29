/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:53:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 21:07:52 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"
#include "defines.hpp"
#include "utils.hpp"

Application*	Application::_instance = NULL;

Application::Application(std::string const & port, std::string const & password)
{
	int	p;

	if (port.find_first_not_of("0123456789") != port.npos)
		throw RuntimeException(ERR_PNAN);
	p = std::atoi(port.c_str());
	if (p <= 1023 || p >= UINT16_MAX)
		throw RuntimeException(ERR_PINV);
	_data = new DAL(password);
	try {
		_serv = new Server(static_cast<unsigned short>(p), _data);
	}
	catch (const std::exception& e)
	{
		delete _data;
		throw RuntimeException(e.what());
	}
	_parser = new Parser(_serv);
	_handler = new CommandHandler(_serv, *_data);
}

Application::~Application(void)
{
	delete _handler;
	delete _parser;
	delete _serv;
	delete _data;
}

void	Application::destroyInstance(void)
{
	delete _instance;
	_instance = NULL;
}

void	Application::process(void)
{
	request_data_container_t&	requests = _data->getRequestDataContainer();

	while (requests.size() != 0)
	{
		std::cout << "Message before parsing: " << requests.front().what;
		std::vector<IRCMessage>	messages = \
			_parser->parseMessage(requests.front().what, requests.front().who);
		// _parser->prettyPrint(messages);
		for (ircmessage_iterator_t it = messages.begin(); \
			it != messages.end(); it++)
		{
			try
			{
				_handler->handle(_data->findClient(\
							requests.front().who->getFd()), *it);
			}
			catch (std::exception& e)
			{
				_serv->reply(requests.front().who, e.what());
			}
		}
		requests.pop();
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
