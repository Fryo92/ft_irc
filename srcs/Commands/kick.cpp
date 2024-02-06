#include "Server.hpp"
#include "utils.hpp"

void	Server::kick(Client &client){
	std::string err;
	if (client.getBuf().size() < 3) {
		err = ERR_NEEDMOREPARAMS(client.getHost(), client.getBuf()[0]);
		send(client.getSocket(), err.c_str(), err.size(), 0);
		return ;
	}
	if (searchClientChannel(client) != 2){
		err = ERR_NOSUCHCHANNEL(client.getBuf()[1]);
		send(client.getSocket(), err.c_str(), err.size(), 0);
		return ;
	}
	if (is_on_channel(client, client.getBuf()[1]))
		return ;
	if (is_op(client, client.getNickName()) == -1){
		err = ERR_CHANOPRIVSNEEDED(client.getChannel().getName());
		send(client.getSocket(), err.c_str(), err.size(), 0);
		return ;
	}
	for (std::vector<std::string>::iterator ite = client.getChannel().getUsers().begin(); ite != client.getChannel().getUsers().end(); ite++) {
		if (client.getBuf()[2] == *ite)
			client.getChannel().getUsers().erase(ite);
	}
}