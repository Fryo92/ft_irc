#include "Server.hpp"


void	Server::topic(Client &client) {

	if (client.getBuf().size() == 1)
	{
		std::string rpl;
		if (client.getChannel().getTopic().size() > 0)
			rpl = RPL_TOPIC(user_id(client.getUserName(), client.getNickName()), client.getChannel().getName(), client.getChannel().getTopic());
		else
			rpl = RPL_NOTOPIC(user_id(client.getUserName(), client.getNickName()), client.getChannel().getName());
		send(client.getSocket(), rpl.c_str(), rpl.size(), 0);
	}
	else
	{
		std::string topic;

		for (size_t i = 1; i < client.getBuf().size(); i++){
			topic += client.getBuf()[i];
			if (i < client.getBuf().size() - 1)
				topic += " ";
		}
		client.getChannel().setTopic(topic);
	}	
}