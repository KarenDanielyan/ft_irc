/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:16:18 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/27 22:27:19 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "IRCMessage.hpp"
# include <sstream>


class Parser
{
	private:
		IRCMessage	_message;
	public:
		Parser();
		~Parser();
	public:
		std::vector<std::string>	parseParameters(const std::string& rawParams);
		int 						parseMessage(const std::string& rawMessage);
		void 						setMessage(const IRCMessage& message); 
		const IRCMessage& 			getMessage();
};

#endif
