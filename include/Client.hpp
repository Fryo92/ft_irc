#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

class Client
{
	private:
		int	_clientSocket;
		int	_clientPort;
		struct sockaddr_in _clientAddr;
		socklen_t _clientLen;
		std::string _clientIP;



	public:
		Client();
		~Client();

		int initClient(Server server);
		int getclientSocket() const {return _clientSocket;};
};


#endif