/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:51:28 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/25 13:56:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

#include <iostream>

int main()
{
	IRCParser parser;
	std::vector<std::string> testMessages = {
		"@time=12345;key=value :source PRIVMSG #channel :Hello, world!",
		"NICK new_user",
		"JOIN #channel1,#channel2",
		"PRIVMSG #channel :Hello there!",
		"PART #channel",
		"PONG server1"
	};
	for (const auto& message : testMessages)
	{
		try {
			parser.parseMessage(message);
			const IRCMessage& ircMessage = parser.getMessage();
			std::cout << "Parsed message:\n";
			std::cout << "Command: " << ircMessage._command << "\n";
			std::cout << "Source: " << ircMessage._source << "\n";
			std::cout << "Tags: \n";
			for (const auto& tag : ircMessage._tags) {
				std::cout << "  " << tag.first << "=" << tag.second << "\n";
			}
			std::cout << "Parameters: \n";
			for (const auto& param : ircMessage._parameters) {
				std::cout << "  " << param << "\n";
			}
			std::cout << std::endl;
		} catch (const std::invalid_argument& e) {
			std::cout << "Error parsing message: " << e.what() << std::endl;
		}
	}

	return 0;
}