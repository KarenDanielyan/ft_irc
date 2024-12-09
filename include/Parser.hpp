#ifndef _parser_
#define _parser_


# define Cap 1
# define Who 2
# define Pass 3
# define Join 4
# define Kick 5
# define Mode 6
# define Quit 7
# define Nick 8
# define Pong 9
# define Ping 10
# define Part 11
# define Topic 12
# define Notice 13
# define Invite 14
# define PrivMsg 15
# define UserCmd 16

#include "Command_Data.hpp"


#define val "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

class Parser
{
	private:
		Message* message;
	public:
		static bool	check_arguments(std::string&); // check command + parametr if its rigth form
		static void	fill_client_command(std::string&); // fill all the data to cmd 
		static int	check_command(Message& message); // check command return its value depends on macros
		static bool	check_commmand_cap(Message& cmd); // validateion for command cap
		static bool	check_commmand_who(Message& cmd); // validateion for command who
		static bool	check_commmand_pass(Message& cmd); // validateion for command pass
		static bool	check_commmand_join(Message& cmd); // validateion for command join
		static bool	check_commmand_kick(Message& cmd); // validateion for command kick
		static bool	check_commmand_mode(Message& cmd); // validateion for command mode
		static bool	check_commmand_quit(Message& cmd); // validateion for command quit
		static bool	check_commmand_nick(Message& cmd); // validateion for command nick
		static bool	check_commmand_pong(Message& cmd); // validateion for command pong
		static bool	check_commmand_ping(Message& cmd); // validateion for command ping
		static bool	check_commmand_part(Message& cmd); // validateion for command part
		static bool	check_commmand_topic(Message& cmd); // validateion for command topic
		static bool	check_commmand_notice(Message& cmd); // validateion for command notice
		static bool	check_commmand_invite(Message& cmd); // validateion for command invite
		static bool	check_commmand_privmsg(Message& cmd); // validateion for command privmsg
		static bool	check_commmand_usercmd(Message& cmd); // validateion for command usercmd
};







#endif