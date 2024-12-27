/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:47:13 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 22:47:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "defines.hpp"
# include <map>
# include <vector>
# include <iostream>

struct IRCMessage
{
	std::map<std::string, std::string> tags;
	std::string source;
	std::string command;
	std::vector<std::string> parameters;
	IRCMessage() : tags(), source(""), command(""), parameters() {}
};

#endif
