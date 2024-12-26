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

class DAL
{
	private:
		std::map<int, Client *>&			_clients;
		std::vector<Channel *>&				_channels;
		std::string							_password;
	public:
		DAL(std::map<int, Client *>& clients, \
			std::vector<Channel *>& channels);
		~DAL();

		Client*					getClient(std::string nick);
		std::vector<Client *>	getClients(void);
		Channel*				getChannel(std::string name);
		std::string const &		getPassword();

		void					addChannel(std::string name, std::string topic, \
			std::string pass, Client* client);

};

#endif