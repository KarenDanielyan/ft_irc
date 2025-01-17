/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariam <mariam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:33:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 02:02:23 by mariam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAL_HPP
# define DAL_HPP

# include "Client.hpp"
# include "Server.hpp"
# include "Channel.hpp"
# include "defines.hpp"

class DAL
{
	private:
		std::map<int, Client *>			_clients;
		std::vector<Channel *>			_channels;
		std::string						_password;

		request_data_container_t		_requests;
	public:
		DAL(std::string const & password): _password(password) {};
		~DAL();

		/* Read Methods */
		Client*			findClient(int fd);
		Client*			findClient(std::string nickname);
		std::map<int, Client *>& \
						getClients(void);
		Channel*		getChannel(std::string name);
		std::string const & \
						getPassword();
		request_data_container_t& \
						getRequestDataContainer(void);

		/* Write Methods */
		void			newClient(Connection *connection);
		void			removeClient(Client *client);
		void			addChannel(std::string& name, std::string& topic, \
			std::string& pass, Client* client);

};

#endif
