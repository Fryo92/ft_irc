#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"


# define user_id(user, nick) ":" + user + "!" + nick + "@localhost"

# define ERR_NOSUCHNICK(host, nick) host + " 401 " + nick + " :No such nick/channel"
# define ERR_UNKNOWNCOMMAND(host, command) ":localhost 421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(host) host + " 431 :No nick name given"
# define ERR_ERRONEUSNICKNAME(host, nickname) host + " 432 " + nickname + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(host, nickname) host + " 433 " + nickname + " :Nickname is already in use"
# define ERR_NOTREGISTERED(host) host + " 451 :You have not registered"
# define ERR_NEEDMOREPARAMS(host, command) host + " 461 " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(host) host + " 462 :You may not reregister"
# define ERR_PASSWDMISMATCH(host) host + " 464 :Password incorrect"
# define ERR_UNKNOWNMODE(host, ch) host + " 472 " + ch + " :is unknown mode char to me"
# define ERR_USERSDONTMATCH(host) host + " 502 :Cant change mode for other users"
# define ERR_ERRONEUSUSER(host, user) host + " " + user + " :Erroneus user"

# define RPL_WELCOME(user_id, nick) ":localhost 001 " + nick + " :Welcome to the Internet Relay Network " + user_id + "\r\n"
# define RPL_QUIT(user_id, reason) user_id + " QUIT :Quit: " + reason + "\r\n"
# define RPL_UMODEIS(client, mode) ":localhost 221 " + client + " " + mode + "\r\n"
# define MODE_USERMSG(client, mode) ":" + client + " MODE " + client + " :" + mode + "\r\n"





#endif
