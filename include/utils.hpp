#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"


# define user_id(user, nick) ":" + user + "!" + nick + "@localhost"

# define ERR_UNKNOWNCOMMAND(server, command) server + " 421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(server) server + " 431 :No nick name given"
# define ERR_ERRONEUSNICKNAME(server, nickname) server + " 432 " + nickname + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(server, nickname) server + " 433 " + nickname + " :Nickname is already in use"
# define ERR_NEEDMOREPARAMS(server, command) server + " 461 " + command + " :Not enough parameters"
# define ERR_NOTREGISTERED(server) server + " 451 :You have not registered"
# define ERR_ALREADYREGISTRED(server) server + " 462 :You may not reregister"
# define ERR_PASSWDMISMATCH(server) server + " 464 :Password incorrect"
# define ERR_ERRONEUSUSER(server, user) server + " " + user + " :Erroneus user"

# define RPL_WELCOME(user_id, nick) ":localhost 001 " + nick + " :Welcome to the Internet Relay Network " + user_id + "\n"




#endif
