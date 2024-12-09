#ifndef _message_
#define _message_


class Message
{
	private:
		Client						*client_;
		Server						*server_;
		std::string					command_;
		std::vector<std::string>	parametrs_;
	public:
		Client* 					get_client(void);
		std::string					get_command(void);
		std::vector<std::string>	get_parametrs(void);
		Server*						get_server(void);
	public:
		void						set_server(Server& server);
		void						set_clinet(Clinet& client);
		void						set_command(std::string& command);
		void						set_parametrs(std::vector<std::string>& parametrs);
};


#endif