#include "Server.hpp"

Server::Server(){

}

Server::~Server(){

}

Server::Server(int port, std::string pass) : _port(port), _name("MyIRC_uWu"), _password(pass), _activeClients(0), _shutdown(false) {
	
	for (size_t i = 0; i < _password.size(); i++)
	{
		if (_password[i] == 32 || (_password[i] >= 9 && _password[i] <= 13))
			throw (std::runtime_error("Invalid password."));
	}
	
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1) {
		throw (std::runtime_error("Server socket error."));
	}

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_size = sizeof(sockaddr_in);

	int reuse = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
		close(_socket);
		throw (std::runtime_error("Error setting socket options."));
	}

	if (bind(_socket, (struct sockaddr *)&_addr, _size) == -1) {
        close(_socket);
       	throw (std::runtime_error("Error binding server."));

    }

	if (listen(_socket, MAX_CLIENTS) == -1) {
        close(_socket);
        throw (std::runtime_error("Error listening connexion."));
    }

	memset(_fds, 0, sizeof(_fds));
	_fds[0].fd = _socket;
	_fds[0].events = POLLIN;
	std::cout << _name << " server started on port " << _port << std::endl;

}

void	Server::process() {
	while (_shutdown == false) {
		_pollRet = poll(_fds, _activeClients + 1, -1);
		if (_pollRet == -1){
			closeSocket();
			throw (std::runtime_error("POOOOOLLLLLIIINN"));
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
			clientsManage[clientSocket] = client;
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
			char buffer[1024];
			int bytesRead = recv(_fds[i].fd, buffer, sizeof(buffer) - 1, 0);

			if (bytesRead > 0) {
				buffer[bytesRead] = '\0';
				clientsManage[_fds[i].fd].setBuf(buffer);
				applyCommand(clientsManage[_fds[i].fd]);
			} else {
				if (bytesRead == 0)
                    std::cout << "Client " << i << " disconnected" << std::endl;
				else
                    std::cerr << "Error client " << i << " data" << std::endl;
				deleteClient(clientsManage[_fds[i].fd]);
				i--;
			}
		}
	}
}

void	Server::deleteClient(Client client) {
	int i = 1;
	while (i <= _activeClients){
		if (_fds[i].fd == client.getSocket())
			break;
		i++;	
	}
	close(client.getSocket());

	clientsManage.erase(client.getSocket());
	_activeClients--;

	for (int j = i; j <= _activeClients; ++j)
		_fds[j] = _fds[j + 1];	
}

void	Server::initCommands(){
	commands["/nick"] = &Server::nick;
	commands["/pass"] = &Server::pass;
	commands["/user"] = &Server::user;
}

void	Server::applyCommand(Client client) {
	if (commands[client.getBuf()[0]])
		commands[client.getBuf()[0]](client);\
	else
		std::cerr << ERR_UNKNOWNCOMMAND(_name, client.getBuf()[0]) << std::endl;
}