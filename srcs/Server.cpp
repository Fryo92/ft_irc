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
	initCommands();
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
				if (bytesRead < 0)
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
	std::cout << "Client " << i - 1 << " disconnected" << std::endl;
	clientsManage.erase(client.getSocket());
	_activeClients--;

	for (int j = i; j <= _activeClients; ++j)
		_fds[j] = _fds[j + 1];	
}

void	Server::initCommands(){
	commands["CAP"] = &Server::cap;
	commands["NICK"] = &Server::nick;
	commands["PASS"] = &Server::pass;
	commands["USER"] = &Server::user;
}

void	Server::applyCommand(Client &client) {
	std::map<std::string, CommandFunction> ::iterator it = commands.find(ft_toupper(client.getBuf()[0]));
	if (it != commands.end())
		(this->*(it->second))(client);
	else
		std::cerr << ERR_UNKNOWNCOMMAND(_name, client.getBuf()[0]) << std::endl;
	client.getBuf().clear();
}

std::string	Server::ft_toupper(std::string &str){
	for (size_t i = 0; i < str.size(); i++)
		str[i] = std::toupper(str[i]);
	return (str);	
}

void	Server::cap(Client &client){
	if (!client.getIrssi()){
		for (size_t i = 0; i < client.getBuf().size(); i++){
			if (client.getBuf()[i] == "PASS"){
				if (client.getBuf()[i + 2] != "NICK"){
					std::cerr << ERR_PASSWDMISMATCH(_name) << std::endl;
					return;
				}
				else if (client.getBuf()[i + 1] != _password){
					std::cerr << ERR_PASSWDMISMATCH(_name) << std::endl;
					return;
				}
				else
					client.setPass(client.getBuf()[i + 1]);
			}
			if (client.getBuf()[i] == "NICK"){
				for (std::map<int, Client>::iterator ite = clientsManage.begin(); ite != clientsManage.end(); ite++)
				{
					if (ite->second.getNickName() == client.getBuf()[i + 1])
						client.getBuf()[i + 1] += _activeClients;

				}
				client.setNickName(client.getBuf()[i + 1]);
			}
			if (client.getBuf()[i] == "USER"){
				std::string nick;
				for (int j = i + 1; client.getBuf()[j] != "localhost"; j++){
					nick += client.getBuf()[j];
					if (client.getBuf()[j + 1] != "localhost")
						nick += " ";
				}
				client.setUserName(nick);
			}
			if (client.getBuf()[i] == "localhost")
			{
				std::string real;
				for (size_t j = i; j < client.getBuf().size(); j++)
				{
					real += client.getBuf()[j];
					if ((j + 1) != client.getBuf().size())
						real += " ";
				}
				client.setRealName(real);
			}
		}
		client.setRpl(RPL_WELCOME(user_id(client.getUserName(), client.getNickName()), client.getNickName()));
		// const char* welcomeMessage = ":localhost 001 abiddane :Welcome to the IRC server!\n";
		send(client.getSocket(), client.getRpl().c_str(), client.getRpl().size(), 0);
		// send(client.getSocket(), welcomeMessage, std::strlen(welcomeMessage), 0);
		std::cout << client.getRpl() << std::endl;
	}
	else
		std::cerr << ERR_UNKNOWNCOMMAND(_name, client.getBuf()[0]) << std::endl;		
}