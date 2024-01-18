#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdlib>
# include <cstring>
# include <csignal>
# include <poll.h>
# include <vector>
# include <map>
# include "Client.hpp"

# define MAX_CLIENTS 5

class Server {
	private:
		Server();

		int	_socket;
		int	_port;
		std::string	_password;
		sockaddr_in _addr;
		socklen_t _size;

		pollfd _fds[MAX_CLIENTS + 1];
		int _pollRet;

		int _activeClients;
		std::vector<Client> clientsManage;

		std::map<std::string, void(*)(const std::string, Client)> command;

		bool	_shutdown;

	public:
		~Server();
		Server(int port, std::string pass);

		void	process();
		void	closeSocket();
		void	createClient();
		void	deleteClient(int i);
		void	listenClient();
		void	initCommandMap();
		void	applyCommand();

};

#endif