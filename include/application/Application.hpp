/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:02:37 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 21:25:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include "defines.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class	Application
{
private:
	static Application*			_instance;

	request_data_container_t	_requests;

	Server*						_serv;

	std::string					_password;
	std::vector<Channel *>		_channels;
	std::map<int, Client*>		_clients;


	Application(std::string const & port, \
			 std::string const & password);
	~Application();

	void	process(void);
public:
	static Application*	getInstance(std::string const & port, \
						std::string const & password);
	static void			destroyInstance(void);
	void				run(void);
};

#endif
