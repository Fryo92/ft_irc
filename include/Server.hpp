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
# include <functional>
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

		std::map<std::string, std::function<void(Client)>> commands;

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
		void	applyCommand(Client client);

		void	nick(Client client);
		void	user(Client client);
		void	pass(Client client);

};

#endif