/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:16:18 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/28 20:10:52 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "IRCMessage.hpp"
# include "Server.hpp"
# include "utils.hpp"
# include <sstream>
# include "Connection.hpp"

class Parser
{
	private:
		ITransport*				_server;

		IRCMessage	_fillIRCMessage(const std::string& line, Connection* from);
	public:
		Parser(ITransport* server);
		~Parser();

		std::vector<IRCMessage> \
					parseMessage(std::string& rawMessage, Connection *from);
		void		prettyPrint(std::vector<IRCMessage> const & messages);
};

#endif
