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
#include "CommandHandler.hpp"
#include "IRCClient.hpp"

int	main(int ac, char **av)
{
	Server*	serv;
	CommandHandler* command;
	IRCClient* client;

	if (ac != 3)
		std::cout << USAGE_MSG << std::endl;
	else
	{
		std::vector<std::string> args(av, av + ac);

		serv = Server::getInstance(av[1], av[2]);
		command = new CommandHandler(serv);
		const std::string host = "hostname";
		// IRCClient(int fd, char *hostname, unsigned short port);

		client = new IRCClient(1, const_cast<char*>(host.c_str()), 8888);
		client->setNickname("marihovh");
		try
		{
			std::vector<std::string> arg;
			arg.push_back("PRIVMSG");
			arg.push_back("#wef");
			arg.push_back("es");


			command->Handler(client, arg, "Topic");
			// serv->start();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	Server::destroyInstance();
	return (0);
}
