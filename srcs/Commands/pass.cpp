#include "Server.hpp"

void	Server::pass(Client client){
	
	if (client.getBuf().size() == 1)
		std::cerr << ERR_NEEDMOREPARAMS(_name, client.getBuf()[0]) << std::endl;
	else if (client.getBuf().size() > 2)
		std::cerr << ERR_PASSWDMISMATCH(_name) << std::endl;
	else if (!client.getPass().empty())
	{
		if (client.getBuf()[1].compare(_password))
		{
			std::cerr << ERR_PASSWDMISMATCH(_name) << std::endl;
			deleteClient(client);
			return ;
		}
		else 
			client.setPass(client.getBuf()[1]);
	}
	else
		std::cerr << ERR_ALREADYREGISTRED(_name) << std::endl;
	client.getBuf().clear();
}