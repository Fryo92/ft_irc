#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdio> // Inclusion nécessaire pour perror
#include <csignal>
#include "irc.hpp"

int main(int ac, char **av) {

    if (ac == 3){

        Server server(std::atoi(av[1]), av[2]);

        int  ret = server.initServer();
        if (ret){
            if (ret == 1)
                close(server.getServerSocket());
            return 1;
        }

        // Accepter les connexions entrantes
        while (true) {
            
            Client client;

            if (client.initClient(server))
                break ;

            // Envoyer un message de bienvenue
            const char *welcomeMessage = "Welcome to IRC Server!\n";
            send(client.getclientSocket(), welcomeMessage, strlen(welcomeMessage), 0);

            // Boucle pour maintenir la connexion ouverte
            char buffer[1024];
            int bytesReceived;
            while (true) {
                bytesReceived = recv(client.getclientSocket(), buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    break; // Déconnexion du client
                }
                buffer[bytesReceived] = '\0';
                std::cout << "Message reçu du client : " << buffer << std::endl;
                // Vous pouvez ajouter ici le traitement des messages reçus du client
            }

            // Fermeture de la connexion lorsque le client se déconnecte
            close(client.getclientSocket());
        }

        close(server.getServerSocket());
    }
    else
        std::cerr << "Wrong number of arguments" << std::endl;
    return 0;
}
