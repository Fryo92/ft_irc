#include "Server.hpp"

Server::Server(){

}

Server::~Server(){

}

Server::Server(int port, std::string pass) : _port(port), _password(pass), _activeClients(0), _shutdown(false) {
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1) {
		std::cerr << "Server socket error." << std::endl;
		throw;
	}

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_size = sizeof(sockaddr_in);

	int reuse = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
		close(_socket);
		std::cerr << "Error setting socket options." << std::endl;
		throw;
	}

	if (bind(_socket, (struct sockaddr *)&_addr, _size) == -1) {
        close(_socket);
		std::cerr << "Error binding server." << std::endl;
        throw;
    }

	if (listen(_socket, MAX_CLIENTS) == -1) {
        close(_socket);
		std::cerr << "Error listening connexion." << std::endl;
        throw;
    }

	memset(_fds, 0, sizeof(_fds));
	_fds[0].fd = _socket;
	_fds[0].events = POLLIN;
	std::cout << "IRC server started on port " << _port << std::endl;

}

void	Server::process() {
	while (_shutdown == false) {
		_pollRet = poll(_fds, _activeClients + 1, -1);
		if (_pollRet == -1){
			std::cerr << "POOOOOLLLLLIIINN" << std::endl;
			closeSocket();
			throw;
		}

		if (_fds[0].revents & POLLIN)
			createClient();

		listenClient();
	}
}

void	Server::closeSocket(){
	for (int i = 0; i <= _activeClients; i++)
		close(_fds[i].fd);
}

void	Server::createClient(){
	sockaddr_in clientAddr;
	socklen_t clientSize = sizeof(sockaddr_in);
	int clientSocket = accept(_socket, (sockaddr *)&clientAddr, &clientSize);
	if (clientSocket == -1)
	    std::cerr << "Error client connection" << std::endl;        
	else {
		if (_activeClients < MAX_CLIENTS){
			Client client(clientSocket, clientAddr);
			clientsManage.push_back(client);
			_activeClients++;
			_fds[_activeClients].fd = clientSocket;
			_fds[_activeClients].events = POLLIN;
			send(clientSocket, "Welcome to IRC Server!\n", 23, 0);
		} else {
			std::cerr << "Max clients number reach" << std::endl;
			close(clientSocket);
		}
	}
}

void	Server::listenClient() {
	for (int i = 1; i <= _activeClients; i++) {
		if (_fds[i].revents & POLLIN) {
			std::cout << "ici" << std::endl;
			char buffer[1024];
			int bytesRead = recv(_fds[i].fd, buffer, sizeof(buffer) - 1, 0);

			if (bytesRead > 0) {
				buffer[bytesRead] = '\0';
				std::cout << "Server says: " << buffer << std::endl;
				if (strncmp(buffer, "quitter", 7) == 0)
        			_shutdown = true;
			} else {
				if (bytesRead == 0)
                    std::cout << "Client " << i << " disconnected" << std::endl;
				else
                    std::cerr << "Error client " << i << " data" << std::endl;
				deleteClient(i);
				i--;
			}
		}
	}
}

void	Server::deleteClient(int i) {
	close(_fds[i].fd);

	clientsManage.erase(clientsManage.begin() + i);
	_activeClients--;

	for (int j = i; j <= _activeClients; ++j)
		_fds[j] = _fds[j + 1];	
}

void	initCommandMap();

void	applyCommand();