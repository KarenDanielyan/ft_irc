/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:02:37 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 17:08:07 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef APPLICATION_HPP
# define APPLICATION_HPP

// TODO: Add the parser and command handler on readiness
# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class	Application
{
private:
	static Application*		_instance;
	Server*					_serv;

	std::string				_password;
	std::vector<Channel *>	_channels;
	std::map<int, Client*>	_clients;

	Application(std::string const & port, \
			 std::string const & password);
	~Application();
public:
	typedef std::vector<Channel*>::iterator		channel_iterator_t;
	typedef std::map<int, Client*>::iterator	clients_iterator_t;

	static Application*	getInstance(std::string const & port, \
						std::string const & password);
	static void			destroyInstance(void);
	void				run(void);
};

#endif
