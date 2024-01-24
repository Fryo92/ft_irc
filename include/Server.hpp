#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cctype>
# include <cstdlib>
# include <cstring>
# include <csignal>
# include <poll.h>
# include <vector>
# include <map>
# include <sstream>
# include "Client.hpp"
# include "utils.hpp"

# define MAX_CLIENTS 5

class Server {
	private:
		Server();

		int	_socket;
		int	_port;
		std::string _name;
		std::string	_password;
		sockaddr_in _addr;
		socklen_t _size;

		pollfd _fds[MAX_CLIENTS + 1];
		int _pollRet;

		int _activeClients;
		std::map<int, Client> clientsManage;

		typedef void (Server::*CommandFunction)(Client&);
    	std::map<std::string, CommandFunction> commands;

		bool	_shutdown;


	public:
		~Server();
		Server(int port, std::string pass);

		void	process();
		void	closeSocket();
		void	createClient();
		void	deleteClient(Client client);
		void	listenClient();
		void	initCommands();
		void	applyCommand(Client &client);

		void	cap(Client &client);
		void	nick(Client &client);
		void	user(Client &client);
		void	pass(Client &client);
		void	pong(Client &client);
		void	mode(Client &client);
		void	privmsg(Client &client);
		void	quit(Client &client);

		void	nickIrssi(Client &client, int i);
		void	userIrssi(Client &client, int i);
		bool	passIrssi(Client &client, int i);

		int	searchClientChannel(Client client);
		std::string	ft_toupper(std::string &str);

};

#endif