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

/*

— i : Définir/supprimer le canal sur invitation uniquement -- /!\ au i du user != i du canal
	if (client.getBuf()[2] == "+i" && client.getMode() == false)
	{
		client.setMode(true);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "+i");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}
	else if (client.getBuf()[2] == "-i" && client.getMode() == true)
	{
		client.setMode(false);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "-i");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}


— t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
	if (client.getBuf()[2] == "+t" && client.getMode() == false)
	{
		client.setMode(true);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "+t");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}
	else if (client.getBuf()[2] == "-t" && client.getMode() == true)
	{
		client.setMode(false);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "-t");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}


— k : Définir/supprimer la clé du canal (mot de passe)
	if (client.getBuf()[2] == "+k" && client.getMode() == false)
	{
		client.getChannel().setPass(mdp);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "+k");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}
	else if (client.getBuf()[2] == "-k" && client.getMode() == true)
	{
		client.getChannel().clear(le mdp);
		ret = MODE_CHANNELMSG(client.getChannel().getName(), "-k");
		send(client.getSocket(), ret.c_str(), ret.size(), 0);
	}


— o : Donner/retirer le privilège de l’opérateur de canal
{


	
}

— l : Définir/supprimer la limite d’utilisateurs pour le canal
	if (client.getBuf()[2] == "+l" && client.getMode() == false)
	{
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
*/