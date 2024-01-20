#include "Server.hpp"

void	Server::nick(Client &client){
	
	std::string nickname;

	for (size_t i = 1; i < client.getBuf().size(); i++){
		nickname += client.getBuf()[i];
		if (i < client.getBuf().size() - 1)
			nickname += " ";
	}
	if (client.getBuf().size() == 1)
		std::cerr << ERR_NEEDMOREPARAMS(_name, client.getBuf()[0]) << std::endl;
	else if (client.getBuf().size() > 2){
		std::cerr << ERR_ERRONEUSNICKNAME(_name, nickname) << std::endl;
	}
	else if (!client.getPass().empty())
	{
		for (size_t i = 0; i < client.getBuf()[1].size(); i++)
		{
			if (!isalnum(client.getBuf()[1][i]))
			{
				std::cerr << ERR_ERRONEUSNICKNAME(_name, nickname) << std::endl;
				client.getBuf().clear();
				return ;
			}
		}
		for (std::map<int, Client>::iterator ite = clientsManage.begin(); ite != clientsManage.end(); ite++)
		{
			if (nickname == ite->second.getNickName())
			{
				std::cerr << ERR_NICKNAMEINUSE(_name, nickname) << std::endl;
				client.getBuf().clear();
				return ;
			}
		}
		
		if (client.getBuf()[1].size() > 9)
			client.setNickName(client.getBuf()[1].substr (0,9));
		else
			client.setNickName(client.getBuf()[1]);
	}
	else {
		std::cerr << ERR_NOTREGISTERED(_name) << std::endl;
		std::cerr << "Enter PASS, NICK, USER in this order" << std::endl;
	}
}