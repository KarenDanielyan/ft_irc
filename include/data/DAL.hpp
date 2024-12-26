/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:33:59 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 23:36:36 by kdaniely         ###   ########.fr       */
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

		void					addChannel(std::string name, std::string pass);
};

#endif