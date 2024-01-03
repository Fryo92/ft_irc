#include "irc.hpp"

Client::Client(){

}

Client::~Client(){

}

int Client::initClient(Server server){

	_clientSocket = accept(server.getServerSocket(), (struct sockaddr *)&_clientAddr, &_clientLen);
	if (_clientSocket < 0) {
		perror("Erreur lors de l'acceptation de la connexion");
		return 1;
	}

	// Récupérer les informations du client
	inet_ntoa(_clientAddr.sin_addr);
	_clientPort = ntohs(_clientAddr.sin_port);
	std::cout << "Connexion acceptée depuis " << _clientIP << ":" << _clientPort << std::endl;
	
	_clientLen = sizeof(_clientAddr);
	
	return 0;
}
