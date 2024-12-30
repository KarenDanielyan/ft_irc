/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:20:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/12/30 11:49:17 by marihovh         ###   ########.fr       */
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

# define BUFFER_SIZE 80
# define CRLF "\r\n"
# define CR '\r'
# define LF '\n'

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
# define INFO_REGISTER "Registration must follow the following order: PASS -> NICK -> USER"

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
# define ERR_ALREADYREGISTERED(source) ("462 " + source + " :You may not reregister")
# define ERR_NEEDMOREPARAMS(source, target) ("461 " + source + " " + target + " :Not enough parameters")
# define ERR_NOSUCHNICK(source, target) ("401 " + source + " " + target + " :No such nick/channel")
# define ERR_NOSUCHCHANNEL(source, target) ("403 " + source + " " + target + " :No such channel")
# define ERR_NONICKNAMEGIVEN(source) ("431 " + source + " :No nickname given")
# define ERR_NICKNAMEINUSE(source, target) ("433 " + source + " " + target + " :Nickname is already in use")
# define ERR_PASSWDMISMATCH(source) ("464 " + source + " :Password incorrect")
# define ERR_UNKNOWNCOMMAND(source, target) ("421 " + source + " " + target + " :Unknown command")
# define ERR_CANNOTSENDTOCHAN(source, target) ("404 " + source + " " + target + " :Cannot send to channel")
# define ERR_NOTONCHANNEL(source, target) ("442 " + source + " " + target + " :You're not on that channel")
# define ERR_CHANOPRIVSNEEDED(source, target) ("482 " + source + " " + target + " :You're not channel operator")
# define ERR_USERNOTINCHANNEL(source, nick, channel) ("441 " + source + " " + nick + " " + channel + " :They aren't on that channel")
# define ERR_USERONCHANNEL(source, nick, channel) ("443 " + source + " " + nick + " " + channel + " :is already on channel")
# define ERR_INVITEONLYCHAN(source, target) ("473 " + source + " " + target + " :Cannot join channel, you must be invited (+i)")
# define ERR_CHANNELISFULL(source, target) ("471 " + source + " " + target + " :Cannot join channel, channel is full (+l)")
# define ERR_BADCHANNELKEY(source, target) ("475 " + source + " " + target + " :Cannot join channel (+k)")
# define ERR_NOTREGISTERED(source) ("451 " + source + " :You have not registered")
# define ERR_UNKNOWNERROR(source, command, info) ("400 " + source + " " + command + " :" + info)

/*command reply*/
# define RPL_USERMODE(source, channel, nickname) (":" + source + " MODE " + channel + " +o " + nickname)
# define RPL_CHANNELMODEIS(name, channel, mode) ("324 " + name + " " + channel + " " + mode)
# define RPL_WELCOME(source, nickname) ("001 " + source + " :Welcome to the ft_irc Network, " + nickname)
# define RPL_PING(source, message) (":" + source + " PONG :" + message)
# define RPL_MSG(source, command, target, message)   ":" + source + " " + command + " " + target + " :" + message
# define RPL_INVITING(source, nick, channel) ("341 " + source + " " + nick + " " + channel)
# define RPL_ENDOFNAMES(source, channel) ("366 " + source +  " " + channel + " :End of /NAMES list")
# define RPL_NAMREPLY(name, channel, prefix, nick) ("353 " + name + " = " + channel + " :" + prefix + nick)
# define RPL_WHOREPLY(source, channel, username, host, server, nick, flags, realname) \
	("352 " + source + " " + channel +  " " + username + " " + host + \
	" " + server + " " + nick + " " + flags + " 0 " + ":" + realname)
# define RPL_TOPIC(source, channel, topic) ("332 " + source + " " + channel + " :" + topic)
# define RPL_JOIN(source, channel) (":" + source + " JOIN " + channel)
# define RPL_PART(source, channel) (":" + source + " PART " + channel)
# define RPL_QUIT(source, reason) (":" + source + " QUIT :Quit: " + reason)
# define RPL_NOTOPIC(source, channel) ("331 " + source + " " + channel + " :No topic is set")
# define RPL_ENDOFWHO(source, mask) ("315 " + source + " " + mask + " :End of WHO list")
# define ERR_TOOMANYCHANNELS(source, target) ("405 " + source + " " + target + " :You have joined too many channels")

/* Nick reply */
# define ERR_BADCHANMASK(source) ("476 " + source + " :Bad Channel Mask")
# define ERR_ERRONEUSNICKNAME(source, command) ("432 " + source + " " + command + " :Erroneous nickname")
# define ERR_INPUTTOOLONG(source) ("417 " + source + " :Input line was too long")

#endif
