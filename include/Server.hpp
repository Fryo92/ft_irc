#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstring>
# include <unistd.h>
# include <sys/socket.h>
# include <cstdio>
# include <netinet/in.h>
# include <arpa/inet.h>

# define MAX_CLIENTS 5

class Server {
	private:
		int	_serverSocket;
		int	_port;
		std::string	_password;
		struct sockaddr_in _serverAddr;
	public:
		Server();
		~Server();
		Server(int pt, std::string pw);

		int	getServerSocket() const {return _serverSocket;};

		int	initServer();

};

#endif