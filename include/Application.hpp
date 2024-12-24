/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:02:37 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 16:28:00 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef APPLICATION_HPP
# define APPLICATION_HPP

// TODO: Add the parser and command handler on readiness
# include "Server.hpp"
# include "IRCClient.hpp"

class	Application
{
private:
	static Application*	_instance;
	Server*				_serv;

	std::string			_password;

	Application(std::string const & port, \
			 std::string const & password);
	~Application();
public:
	static Application*	getInstance(std::string const & port, \
						std::string const & password);
	static void			destroyInstance(void);
	void				run(void);
};

#endif
