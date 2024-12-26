/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransport.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:58:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/26 14:59:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ITRANSPORT_HPP
# define ITRANSPORT_HPP

# include <string>
# include "Connection.hpp"

class	ITransport
{
public:
	virtual void	reply(Connection* to, std::string const & message) = 0;
	virtual void	broadcast(std::string const & message) = 0;

	virtual ~ITransport() {}
};



#endif
