/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransport.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:58:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 21:38:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ITRANSPORT_HPP
# define ITRANSPORT_HPP

# include <string>

class Connection;

class	ITransport
{
public:
	virtual void	reply(const Connection* to, std::string const & message) = 0;
	virtual void	broadcast(Connection* sender, std::string const & message) = 0;

	virtual ~ITransport() {}
};

#endif
