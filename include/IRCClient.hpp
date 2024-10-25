/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/25 15:14:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include "Client.hpp"
# include "Channel.hpp"

class	IRCClient : public Client
{
private:
	Channel	*_channel;
public:
	IRCClient();

	~IRCClient();
};

#endif
