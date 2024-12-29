/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransport.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:58:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 03:58:16 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ITRANSPORT_HPP
# define ITRANSPORT_HPP

# include <string>

class Connection;

class	ITransport
{
public:
	virtual void	reply(const Connection* to, std::string const & message) const = 0;
	virtual void	broadcast(Connection* sender, std::string const & message) const = 0;
	virtual void	closeConnection(const Connection* connection) = 0;

	virtual ~ITransport() {}
};

#endif
