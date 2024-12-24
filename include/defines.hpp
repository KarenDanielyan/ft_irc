/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:20:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/23 18:48:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_HPP
# define DEFINES_HPP

# define MAX_CONNECTIONS 1000
# define HOSTNAME "127.0.0.1"

# define BUFFER_SIZE 80

/* To be used later if we want */
# define MSG_SIZE 512

# define USAGE_MSG "Usage: ./ircserv <port> <password>"

# define SA struct sockaddr
# define SA_IN struct sockaddr_in

/* Info Messages */
# define INFO_LISTEN "Server listens to any new connections..."

/* Error Messages */
# define ERR_PNAN "Error: <port> must contain only numbers!"
# define ERR_PINV "Error: invalid <port>. Expected value in range [1024 ; 65535]."
# define ERR_SCKFAIL "Error: failed to create a socket!"
# define ERR_FNBLCK "Error: failed to put socket into non-blocking mode!"
# define ERR_FBIND "Error: failed to bind socket to a port!"
# define ERR_ADDRBIND "Error: failed to assign a name to a socket!"
# define ERR_CREFUSED "Error: connection refused!"
# define ERR_POLL "Error: polling failed!"
# define ERR_HOSTNAME "Error: cannot retrieve hostname of the IRCClient!"

/*error reply*/
# define ERR_ALREADYREGISTERED(target) (std::string("462 ") + "Error: " + target + " :You may not reregister")
# define ERR_NEEDMOREPARAMS(target) (std::string("461 ") + "Error: " + target + " :Not enough parameters")
# define ERR_NOSUCHNICK(target) (std::string("401 ") + "Error: " + target + " :No such nick/channel")
# define ERR_NOSUCHCHANNEL(target) (std::string("403 ") + "Error: " + target + " :No such channel")
# define ERR_NONICKNAMEGIVEN(target) (std::string("431 ") + "Error: " + target + " :No nickname given")
# define ERR_NICKNAMEINUSE(target) (std::string("433 ") + "Error: " + target + " :Nickname is already in use")
# define ERR_PASSWDMISMATCH(target) (std::string("464 ") + "Error: " + target + " :Password incorrect")
# define ERR_UNKNOWNCOMMAND(target) (std::string("421 ") + "Error:  " + target + " :Unknown command")
# define ERR_CANNOTSENDTOCHAN(target) (std::string("404 ") + "Error:  " + target + " :Cannot send to channel")
# define ERR_NOTONCHANNEL(target) (std::string("442 ") + "Error:  " + target + " :You're not on that channel")
# define ERR_CHANOPRIVSNEEDED(target) (std::string("482 ") + "Error:  " + target + " :You're not channel operator")
# define ERR_USERNOTINCHANNEL(target) (std::string("441 ") + "Error:  " + target + " :They aren't on that channel")
/*command reply*/
# define RPL_CHANNELMODEIS(client, channel, mode, argument) (std::string("324 ") + client + " " + channel + " " +mode + " " +argument)
#endif
