/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:20:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/29 06:11:32 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_HPP
# define DEFINES_HPP

# include <map>
# include <queue>
# include <vector>
# include <string>


/* Forward declarations */
struct	IRCMessage;
struct	RequestData;
struct	pollfd;
class	Connection;
class	Client;
class	Channel;

# define MAX_CONNECTIONS 1000
# define HOSTNAME "127.0.0.1"

# define MAX_MESSAGE_LENGTH 512
# define IGNOR_MESSAGE -1
# define VALID_MESSAGE 1

# define BUFFER_SIZE 80
# define CRNL "\n"

# define USAGE_MSG "Usage: ./ircserv <port> <password>"

# define SA struct sockaddr
# define SA_IN struct sockaddr_in

/* Type definitions */
typedef std::queue<RequestData>					request_data_container_t;
typedef std::map<int, Connection*>::iterator	connection_iterator_t;
typedef std::vector<Channel*>::iterator			channel_iterator_t;
typedef std::map<int, Client*>::iterator		clients_iterator_t;
typedef std::vector<pollfd>::iterator			pollfds_iterator_t;
typedef std::vector<IRCMessage>::iterator		ircmessage_iterator_t;

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
# define ERR_HOSTNAME "Error: cannot retrieve hostname of the Client!"

/*error reply*/
# define ERR_ALREADYREGISTERED(source, target) (source + std::string(" 462 ") + "Error: " + target + " :You may not reregister\n")
# define ERR_NEEDMOREPARAMS(source, target) (source + std::string(" 461 ") + "Error: " + target + " :Not enough parameters\n")
# define ERR_NOSUCHNICK(source, target) (source + std::string(" 401 ") + "Error: " + target + " :No such nick/channel\n")
# define ERR_NOSUCHCHANNEL(source, target) (source + std::string(" 403 ") + "Error: " + target + " :No such channel\n")
# define ERR_NONICKNAMEGIVEN(source, target) (source + std::string(" 431 ") + "Error: " + target + " :No nickname given\n")
# define ERR_NICKNAMEINUSE(source, target) (source + std::string(" 433 ") + "Error: " + target + " :Nickname is already in use\n")
# define ERR_PASSWDMISMATCH(source, target) (source + std::string(" 464 ") + "Error: " + target + " :Password incorrect\n")
# define ERR_UNKNOWNCOMMAND(source, target) (source + std::string(" 421 ") + "Error:  " + target + " :Unknown command\n")
# define ERR_CANNOTSENDTOCHAN(source, target) (source + std::string(" 404 ") + "Error:  " + target + " :Cannot send to channel\n")
# define ERR_NOTONCHANNEL(source, target) (source + std::string(" 442 ") + "Error:  " + target + " :You're not on that channel\n")
# define ERR_CHANOPRIVSNEEDED(source, target) (source + std::string(" 482 ") + "Error:  " + target + " :You're not channel operator\n")
# define ERR_USERNOTINCHANNEL(source, target) (source + std::string(" 441 ") + "Error:  " + target + " :They aren't on that channel\n")
# define ERR_USERONCHANNEL(source, target) (source + std::string(" 443 ") + target + " :is already on channel\n")
# define ERR_INVITEONLYCHAN(source, target) (source + std::string(" 473 ") + target + " :Cannot join channel (+i)\n")
# define ERR_CHANNELISFULL(source, target) (source + std::string(" 471 ") + target + " :Cannot join channel (+l)\n")
# define ERR_BADCHANNELKEY(source, target) (source + std::string(" 471 ") + target + " :Cannot join channel (+k)\n")
# define ERR_USERSDONTMATCH(source) (source + std::string(" 502 ") + " :Cant change mode for other users\n")

/*command reply*/
# define RPL_CHANNELMODEIS(source, channel, mode, argument) (source + std::string(" 324 ") \
	+ " " + channel + " "  +mode + " " +argument + "\n")
# define RPL_WELCOME(source, nick) (source + std::string(" 001 ") + " :Welcome to the IRC  Network, " + nick + "\n")
# define RPL_PING(source, message) (source + std::string(" 5000 ") + " :PING " + message + "\n")
# define RPL_PONG(source, message) (source + std::string(" 5001 ") + " :PONG " + message + "\n")
# define RPL_INVITING(source, nick, channel) (source + std::string(" 341 ") + " " + nick + " " + channel + "\n")
# define RPL_ENDOFNAMES(source, channel) (source + std::string(" 366 ") + channel + " :End of /NAMES list\n")
# define RPL_NAMREPLY(source, channel, nick) (source + std::string(" 353 ") + channel + " :" + nick + "\n")
# define RPL_WHOREPLY(source, nick, username, realname) (source + std::string(" 352 ") + nick + " " + username + " " + realname + "\n")
# define RPL_TOPIC(source, channel, topic) (source + std::string(" 366 ") + channel + " :" + topic + "\n") 
# define RPL_NOTOPIC(source, channel) (source + std::string(" 331 ") + channel + " :No topic is set\n")

/* Nick reply */
# define ERR_BADCHANMASK(channel) (std::string(" 476 ") + channel + " :Bad Channel Mask\n")
# define ERR_ERRONEUSNICKNAME(source, nickname) (source +std::string(" 432 ") + nickname + " ::Erroneus nickname\n")
# define ERR_INPUTTOOLONG(source) (source + std::string(" 417 ") + " :Input line was too long\n")

#endif
