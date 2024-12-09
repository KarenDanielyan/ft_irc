#include "Parser.hpp"


static bool	Parser::check_arguments(std::string&)
{
	// check command + parametr if its rigth form
} 
static void	Parser::fill_client_command(std::string&)
{
	// fill all the data to cmd 
}
static int	Parser::check_command(cmd_data& cmd)
{
	// check command return its value depends on macros
}
static bool	Parser::check_commmand_cap(cmd_data& cmd)
{
	std::vector<std::string> sub_commands = {"LS", "LIST", "REQ", "ACK", "NAK", "NEW", "DEL", "END"};
	// validateion for command cap
}
static bool	Parser::check_commmand_who(cmd_data& cmd) 
{
	// validateion for command who
}

static bool	Parser::check_commmand_pass(cmd_data& cmd) 
{
	cmd->command_ is the PASS
	cmd->parametrs_ is the <parametrs>
	// validateion for command pass
}

static bool	Parser::check_commmand_join(cmd_data& cmd)
{
	
	// validateion for command join
}
static bool	Parser::check_commmand_kick(cmd_data& cmd)
{
	// validateion for command kick
}
static bool	Parser::check_commmand_mode(cmd_data& cmd)
{
	// validateion for command mode
}
static bool	Parser::check_commmand_quit(cmd_data& cmd)
{
	// validateion for command quit
}
static bool	Parser::check_commmand_nick(cmd_data& cmd)
{
	if (cmd.parametrs_.empty())
		return false;

	const std::string& nickname = cmd.parametrs_[0];

	if (nickname.empty())
		return false;
	if (nickname.find_first_not_of(VALID_CHARS) != std::string::npos;)
		return false;

	// check if its in use or not 
	return true;
}
static bool	Parser::check_commmand_pong(cmd_data& cmd)
{
	// validateion for command pong
}
static bool	Parser::check_commmand_ping(cmd_data& cmd)
{
	// validateion for command ping
}
static bool	Parser::check_commmand_part(cmd_data& cmd)
{
	// validateion for command part
}
static bool	Parser::check_commmand_topic(cmd_data& cmd)
{
	// validateion for command topic
}

static bool	Parser::check_commmand_notice(cmd_data& cmd)
{
	// validateion for command notice
}
static bool	Parser::check_commmand_invite(cmd_data& cmd)
{
	// validateion for command invite
}
static bool	Parser::check_commmand_privmsg(cmd_data& cmd)
{
	// validateion for command privmsg
}
static bool	Parser::check_commmand_usercmd(cmd_data& cmd)
{
	// validateion for command usercmd
}