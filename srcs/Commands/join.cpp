#include "Server.hpp"

// int		check_chanpswd(Client &client, Channel &channel)
// {
// 	if (!channel.getPass().empty())
// 	{
// 		if (!client.getBuf()[2].empty())
// 		{
// 			if (client.getBuf()[2] == channel.getPass())
// 				return 0;
// 			else
// 				return 1;
// 		}
// 		return 1;
// 	}
// 	return 0;
// }

void	joinChannel(Client &client, Channel &channel) {
	if (channel.getL() != 0 && channel.getUsers().size() >= channel.getL()) {
		std::string err = ERR_CHANNELISFULL(channel.getName());
		send(client.getSocket(), err.c_str(), err.size(), 0);
		return ;
	}
	if (channel.getI() == true)
	{
		int i = 0;
		for	(size_t i = 0; i < channel.getInvite().size(); i++)
		{
			if (client.getNickName() == channel.getInvite()[i]) {
				i = 1;
				break ;
			}
		}
		if (i == 0) {
			std::string err = ERR_INVITEONLYCHAN(channel.getName());
			send(client.getSocket(), err.c_str(), err.size(), 0);
			return ;
		}
	}
	// if (check_chanpswd(client, channel)) {
	// 	std::string err = ERR_BADCHANNELKEY(channel.getName());
	// 	send(client.getSocket(), err.c_str(), err.size(), 0);
	// 	return ;
	// }
	channel.getUsers().push_back(client.getNickName());
	std::string rpl;
	if (channel.getTopic().size() > 0)
		rpl = RPL_TOPIC(user_id(client.getUserName(), client.getNickName()), channel.getName(), channel.getTopic());
	else
		rpl = RPL_NOTOPIC(user_id(client.getUserName(), client.getNickName()), channel.getName());
	client.setChannel(channel);
	send(client.getSocket(), rpl.c_str(), rpl.size(), 0);
}

void	Server::join(Client& client) {
	
	if (client.getBuf().size() == 1) {
		std::cerr << RED << ERR_NEEDMOREPARAMS(_name, client.getBuf()[0]) << RESET << std::endl;
		return ;
	}

	std::string channelName;

	// for (size_t i = 1; i < client.getBuf().size() - 1; i++){
	// 	channelName += client.getBuf()[i];
	// 	if (i < client.getBuf().size() - 2)
	// 		channelName += " ";
	// }
	for (size_t i = 1; i < client.getBuf().size(); i++){
		channelName += client.getBuf()[i];
		if (i < client.getBuf().size() - 1)
			channelName += " ";
	}
	if (channelName[0] != '#' && channelName[0] != '&' && channelName[0] != '1')
		channelName.insert(0, "#");

	if (channelName.find(',') != std::string::npos || channelName.find(' ') != std::string::npos){
		std::cerr << RED << ERR_NOSUCHCHANNEL(channelName) << RESET << std::endl;
		return ;
	}

	if (client.getBuf().size() > 2) {
		std::cerr << RED << ERR_NOSUCHCHANNEL(channelName) << RESET << std::endl;
		return ;
	}

	for	(int i = 0; i < _activeChannels; i++)
	{
		if (channelName == _channelsList[i].getName())
		{
			joinChannel(client, _channelsList[i]);
			break ;
		}
	}
	if (channelName.size() > 32)
		channelName = channelName.substr(0, 32);

	Channel channel(channelName, client.getNickName());
	_channelsList.push_back(channel);
	_activeChannels++;
	joinChannel(client, channel);
}