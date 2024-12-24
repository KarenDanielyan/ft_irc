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

// #include "Server.hpp"
#include <iostream>

#include "../include/Parser.hpp"

#include <stdexcept>


int main()
{
	IRCParser parser;

	std::cout << "Enter IRC command lines to parse (type 'exit' to quit):\n";

	while (true) {
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input == "exit") {
			break;
		}

		try {
			parser.parseMessage(input);
			const IRCMessage& message = parser.getMessage();

			std::cout << "Parsed IRC Message:\n";

			if (!message._tags.empty()) {
				std::cout << "Tags:\n";
				for (const auto& [key, value] : message._tags) {
					std::cout << "  " << key << " = " << value << "\n";
				}
			} else {
				std::cout << "Tags: None\n";
			}

			if (!message._source.empty()) {
				std::cout << "Source: " << message._source << "\n";
			} else {
				std::cout << "Source: None\n";
			}

			std::cout << "Command: " << message._command << "\n";

			if (!message._parameters.empty()) {
				std::cout << "Parameters:\n";
				for (const auto& param : message._parameters) {
					std::cout << "  " << param << "\n";
				}
			} else {
				std::cout << "Parameters: None\n";
			}

			std::cout << "Command validation passed.\n";

		} catch (const std::exception& e) {
			std::cerr << "Error parsing message: " << e.what() << "\n";
		}
	}

	std::cout << "Exiting program.\n";
	return 0;
}
