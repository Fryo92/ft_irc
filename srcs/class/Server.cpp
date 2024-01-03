#include "irc.hpp"

Server::Server(){

}

Server::~Server(){

}

Server::Server(int pt, std::string pw) : _port(pt), _password(pw) {

}

int	Server::initServer(){
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket < 0){
		perror("Server socket creation failed");
		return 2;
	}
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(_port);
	_serverAddr.sin_addr.s_addr = INADDR_ANY;

	int reuse = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		perror("SO_REUSEADDR configuration error");
		return 1;
	}

	if (bind(_serverSocket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0) {
        perror("Error while binding port to socket");
        return 1;
    }

	if (listen(_serverSocket, MAX_CLIENTS) < 0) {
        perror("Failed listening socket");
        return 1;
    }

	std::cout << "IRC server started on port " << _port << std::endl;
	return 0;
}