#include "Message.hpp"

Client* 					Message::get_client(void)
{
	return this->client_;
}

std::string					Message::get_command(void)
{
	return this->command_;
}

std::vector<std::string>	Message::get_parametrs(void)
{
	return this->parametrs_;
}

void						Message::set_clinet(Clinet& client)
{
	this->client_ = client;
}

void						Message::set_command(std::string& command)
{
	this->command_ = command;
}

void						Message::set_parametrs(std::vector<std::string>& parametrs)
{
	this->parametrs_ = parametrs;
}