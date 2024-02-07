#include "Server.hpp"

int	Server::is_op(Client &client, std::string nickname)
{
	if (client.getChannel().getOwner() == nickname)
		return 1;
	for (size_t i = 0; i < client.getChannel().getOperator().size(); i++){
		if (client.getChannel().getOperator()[i] == nickname)
				return 1;
	}
	return -1;
}

int	Server::is_on_channel(Client &client, std::string channel) {
	if (channel != client.getChannel().getName()) {
		std::string err = ERR_NOTONCHANNEL(channel);
		send(client.getSocket(), err.c_str(), err.size(), 0);
		return 1;
	}
	return 0;
}

std::string	Server::ft_toupper(std::string str) {
	for (size_t i = 0; i < str.size(); i++)
		str[i] = std::toupper(str[i]);
	return (str);	
}

void	Server::closeSocket() {
	for (int i = 0; i <= _activeClients; i++)
		close(_fds[i].fd);
}

void	Server::initCommands() {
	commands["CAP"] = &Server::cap;
	commands["NICK"] = &Server::nick;
	commands["PASS"] = &Server::pass;
	commands["USER"] = &Server::user;
	commands["PING"] = &Server::pong;
	commands["MODE"] = &Server::mode;
	commands["PRIVMSG"] = &Server::privmsg;
	commands["QUIT"] = &Server::quit;
	commands["JOIN"] = &Server::join;
	commands["TOPIC"] = &Server::topic;
	commands["KICK"] = &Server::kick;
	commands["INVITE"] = &Server::invite;
}

void	Server::applyCommand(Client &client) {
	std::map<std::string, CommandFunction> ::iterator it = commands.find(ft_toupper(client.getBuf()[0]));
	if (it != commands.end())
		(this->*(it->second))(client);
	else
		std::cerr << RED << ERR_UNKNOWNCOMMAND(client.getBuf()[0]) << RESET << std::endl;
}
