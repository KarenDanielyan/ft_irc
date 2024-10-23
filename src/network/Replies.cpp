/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <grmartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:15:23 by grmartir          #+#    #+#             */
/*   Updated: 2024/10/23 20:15:24 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replies.hpp"

// Error messages
std::string Replies::ERR_NEEDMOREPARAMS(const std::string& source, const std::string& command) const {
    return "461 " + source + " " + command + " :Not enough parameters";
}

std::string Replies::ERR_NOTONCHANNEL(const std::string& source, const std::string& channel) const {
    return "442 " + source + " " + channel + " :You're not on that channel";
}

std::string Replies::ERR_USERNOTINCHANNEL(const std::string& source, const std::string& nickname, const std::string& channel) const {
    return "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel";
}

std::string Replies::ERR_CHANNELISFULL(const std::string& source, const std::string& channel) const {
    return "471 " + source + " " + channel + " :Cannot join channel (+l)";
}

std::string Replies::ERR_BADCHANNELKEY(const std::string& source, const std::string& channel) const {
    return "475 " + source + " " + channel + " :Cannot join channel (+k)";
}

std::string Replies::ERR_INVITONLYCHAN(const std::string& source, const std::string& channel) const {
    return "473 " + source + " " + channel + " :Cannot join channel (+i)";
}

std::string Replies::ERR_NOSUCHCHANNEL(const std::string& source, const std::string& channel) const {
    return "403 " + source + " " + channel + " :No such channel";
}

std::string Replies::ERR_CHANOPRIVSNEEDED(const std::string& source, const std::string& channel) const {
    return "482 " + source + " " + channel + " :You're not channel operator";
}

std::string Replies::ERR_NONICKNAMEGIVEN(const std::string& source) const {
    return "431 " + source + " :Nickname not given";
}

std::string Replies::ERR_NICKNAMEINUSE(const std::string& source, const std::string& nickname) const {
    return "433 " + source + " " + nickname + " :Nickname is already in use";
}

std::string Replies::ERR_ALREADYREGISTERED(const std::string& source) const {
    return "462 " + source + " :You may not reregister";
}

std::string Replies::ERR_PASSWDMISMATCH(const std::string& source) const {
    return "464 " + source + " :Password incorrect";
}

std::string Replies::ERR_NOTREGISTERED(const std::string& source) const {
    return "451 " + source + " :You have not registered";
}

std::string Replies::ERR_UNKNOWNCOMMAND(const std::string& source, const std::string& command) const {
    return "421 " + source + " " + command + " :Unknown command";
}

std::string Replies::ERR_USERONCHANNEL(const std::string& source, const std::string& target, const std::string& channel) const {
    return "443 " + source + " " + target + " " + channel + " :is already on channel";
}

std::string Replies::ERR_NOSUCHNICK(const std::string& source, const std::string& name) const {
    return "401 " + source + " " + name + " :No such nick/channel";
}

// Response messages
std::string Replies::RPL_WELCOME(const std::string& source, const std::string& prefix) const {
    return "001 " + source + " :Welcome to the Internet Relay Network " + prefix;
}

std::string Replies::RPL_YOURHOST(const std::string& source, const std::string& servername, const std::string& version) const {
    return "002 " + source + " :Your host is " + servername + ", running version " + version;
}

std::string Replies::RPL_CREATED(const std::string& source, const std::string& date) const {
    return "003 " + source + " :This server was created " + date;
}

std::string Replies::RPL_MYINFO(const std::string& source, const std::string& servername, const std::string& version, const std::string& usermodes, const std::string& chanmodes) const {
    return "004 " + source + " :" + servername + " " + version + " " + usermodes + " " + chanmodes;
}

std::string Replies::RPL_NAMREPLY(const std::string& source, const std::string& channel, const std::string& users) const {
    return "353 " + source + " = " + channel + " :" + users;
}

std::string Replies::RPL_ENDOFNAMES(const std::string& source, const std::string& channel) const {
    return "366 " + source + " " + channel + " :End of /NAMES list.";
}

std::string Replies::RPL_INVITING(const std::string& source, const std::string& channel, const std::string& target) const {
    return "341 " + source + " " + channel + " " + target;
}

std::string Replies::RPL_NOTOPIC(const std::string& source, const std::string& channel) const {
    return "331 " + source + " " + channel + " :No topic is set";
}

std::string Replies::RPL_TOPIC(const std::string& source, const std::string& channel, const std::string& topic) const {
    return "332 " + source + " " + channel + " :" + topic;
}

std::string Replies::RPL_WHOREPLY(const std::string& source, const std::string& channel, const std::string& username, const std::string& hostname, const std::string& serverhostname, const std::string& nickname, const std::string& realname) const {
    return "352 " + source + " " + channel + " " + username + " " + hostname + " " + serverhostname + " " + nickname + " H :0 " + realname;
}

std::string Replies::RPL_ENDOFWHO(const std::string& source, const std::string& channel) const {
    return "315 " + source + " " + channel + " :End of WHO list";
}

std::string Replies::RPL_LIST(const std::string& source, const std::string& channel, const std::string& nbUsers, const std::string& topic) const {
    return "322 " + source + " " + channel + " " + nbUsers + " :" + topic;
}

std::string Replies::RPL_LISTEND(const std::string& source) const {
    return "323 " + source + " :End of LIST";
}

std::string Replies::RPL_MODE(const std::string& source, const std::string& channel, const std::string& modes, const std::string& args) const {
    return ":" + source + " MODE " + channel + " " + modes + " " + args;
}

std::string Replies::RPL_PING(const std::string& source, const std::string& token) const {
    return ":" + source + " PONG :" + token;
}

std::string Replies::RPL_QUIT(const std::string& source, const std::string& message) const {
    return ":" + source + " QUIT :" + message;
}

std::string Replies::RPL_JOIN(const std::string& source, const std::string& channel) const {
    return ":" + source + " JOIN :" + channel;
}

std::string Replies::RPL_PART(const std::string& source, const std::string& channel) const {
    return ":" + source + " PART " + channel;
}

std::string Replies::RPL_PART_REASON(const std::string& source, const std::string& channel, const std::string& reason) const {
    return ":" + source + " PART " + channel + " :" + reason;
}

std::string Replies::RPL_KICK(const std::string& source, const std::string& channel, const std::string& target, const std::string& reason) const {
    return ":" + source + " KICK " + channel + " " + target + " :" + reason;
}

std::string Replies::RPL_PRIVMSG(const std::string& source, const std::string& target, const std::string& message) const {
    return ":" + source + " PRIVMSG " + target + " :" + message;
}

std::string Replies::RPL_NOTICE(const std::string& source, const std::string& target, const std::string& message) const {
    return ":" + source + " NOTICE " + target + " :" + message;
}

std::string Replies::RPL_INVITE(const std::string& source, const std::string& target, const std::string& channel) const {
    return ":" + source + " INVITE " + target + " :" + channel;
}
