#include "Server.hpp"

void	Server::user(Client &client){
		
	std::string user;

	for (size_t i = 1; i < client.getBuf().size(); i++){
		user += client.getBuf()[i];
		if (i < client.getBuf().size() - 1)
			user += " ";
	}
	if (client.getBuf().size() == 1)
		std::cerr << ERR_NEEDMOREPARAMS(_name, client.getBuf()[0]) << std::endl;
	else if (client.getBuf().size() > 2){
		std::cerr << ERR_ERRONEUSUSER(_name, user) << std::endl;
	}
	else if (client.getUserName().empty())
	{
		for (size_t i = 0; i < client.getBuf()[1].size(); i++)
		{
			if (!isalnum(client.getBuf()[1][i]))
			{
				std::cerr << ERR_ERRONEUSUSER(_name, user) << std::endl;
				return ;
			}
		}	
		client.setUserName(client.getBuf()[1]);
		client.setVerif();
		client.setRpl(RPL_WELCOME(user_id(client.getUserName(), client.getNickName()), client.getNickName()));
		send(client.getSocket(), client.getRpl().c_str(), client.getRpl().size(), 0);
	}
	else if (client.getNickName().empty() || client.getPass().empty()){
		std::cerr << ERR_NOTREGISTERED(_name) << std::endl;
		std::cerr << "Enter PASS, NICK, USER in this order" << std::endl;
	}
	else
		std::cerr << ERR_ALREADYREGISTRED(_name) << std::endl;
}

void	Server::userIrssi(Client &client, int i){
	std::string user;
	for (int j = i + 1; client.getBuf()[j] != "localhost"; j++){
		user += client.getBuf()[j];
		if (client.getBuf()[j + 1] != "localhost")
			user += " ";
	}
	client.setUserName(user);
}