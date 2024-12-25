/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:16:18 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/24 21:42:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "IRCMessage.hpp"
# include <sstream>

# define IGNOR_MESSAGE -1
# define VALID_MESSAGE 1
# define MESSAGE_TO_LONG 417
# define UNKOWN_CMD 0

class Parser
{
	private:
		IRCMessage	_message;
	public:
		Parser();
		~Parser();
	public:
		std::vector<std::string>	parseParameters(const std::string& rawParams);
		std::string 				decodeEscaped(const std::string& rawValue);
		int 						parseMessage(const std::string& rawMessage);
		const IRCMessage& 			getMessage() const;
};

#endif
