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
	for (std::vector<Channel>::iterator ite = _channelsList.begin(); ite != _channelsList.end(); ite++)
	{
		if (ite->getName() == client.getBuf()[1])
			return 2;
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
	if (search == 2)
	{
		int i;
		for (int ite = 0; ite < _channelsList.size(); ite++)
		{
			if (_channelsList[ite].getName() == client.getBuf()[1])
				i = ite;
		}
		client.setCommandchannel(_channelsList[i]);

		std::string ret;
		if (client.getBuf()[2] == "+i" && client.getMode() == false)
		{
			_channelsList[i].setI(true);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "+i");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
		else if (client.getBuf()[2] == "-i" && client.getMode() == true)
		{
			_channelsList[i].setI(false);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "-i");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}

		if (client.getBuf()[2] == "+t" && client.getMode() == false)
		{
			_channelsList[i].setT(true);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "+t");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
		else if (client.getBuf()[2] == "-t" && client.getMode() == true)
		{
			_channelsList[i].setT(false);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "-t");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}

		if (client.getBuf()[2] == "+k" && client.getMode() == false)
		{
			if (client.getBuf().size() == 4)
				client.getCommandchannel().setPass(client.getBuf()[3]);
			else
				
			// if ()
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "+k");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
		else if (client.getBuf()[2] == "-k" && client.getMode() == true)
		{
			// client.getChannel().clear(le mdp);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "-k");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}

		if (client.getBuf()[2] == "+l" && client.getMode() == false)
		{
			if (client.getBuf()[3].size() > 10)
			{
				std::string err = ERR_BADMODEL(_name);
				send(client.getSocket(), err.c_str(), err.size(), 0);
				return ;
			}
			long long l = std::atoi(client.getBuf()[3].c_str());
			if (l < 1 || l > 2147483647)
			{
				std::string err = ERR_BADMODEL(_name);
				send(client.getSocket(), err.c_str(), err.size(), 0);
				return ;
			}
			client.getChannel().setL(l);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "+l");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
		else if (client.getBuf()[2] == "-l" && client.getMode() == true)
		{
			client.getChannel().setL(0);
			ret = MODE_CHANNELMSG(client.getChannel().getName(), "-l");
			send(client.getSocket(), ret.c_str(), ret.size(), 0);
		}
	}
}

/*

— i : Définir/supprimer le canal sur invitation uniquement -- /!\ au i du user != i du canal
	
*/