#include "Server.hpp"
#include "utils.hpp"

int	searchMode(std::string *tab, std::string search, int size){
	for (int i = 0; i < size; i++){
		if (search == tab[i])
			return i;
	}
	return -1;
}

int Server::searchClientChannel(Client client){
	for (std::map<int, Client>::iterator ite = clientsManage.begin(); ite != clientsManage.end(); ite++)
	{
		if (ite->second.getNickName() == client.getBuf()[1])
			return 1;
	}
	return 0;
}

void	Server::mode(Client &client) {
	if (client.getBuf().size() == 2 && client.getBuf()[1] == client.getNickName()){
		std::string mode = "+";
		if (client.getMode())
			mode += "i";	
		std::string ret = RPL_UMODEIS(client.getNickName(), mode);
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
		return ;
	}
	int search = searchClientChannel(client);
	if (search == 1)
	{
		std::string ret;
		if (client.getBuf()[2] == "+i" && client.getMode() == false)
		{
			client.setMode(true);
			ret = MODE_USERMSG(client.getNickName(), "+i");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
		else if (client.getBuf()[2] == "-i" && client.getMode() == true)
		{
			client.setMode(false);
			ret = MODE_USERMSG(client.getNickName(), "-i");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
	}

}