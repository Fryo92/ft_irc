#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[1;96m"
#define WHITE_BOLD "\033[1;97m"

# define user_id(user, nick) ":" + user + "!" + nick + "@localhost"

# define ERR_NOSUCHNICK(host, nick) host + " 401 " + nick + " :No such nick/channel"
# define ERR_NOSUCHCHANNEL(channel) ":localhost 403 " + channel + " :No such channel"
# define ERR_UNKNOWNCOMMAND(command) ":localhost 421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(host) host + " 431 :No nick name given"
# define ERR_ERRONEUSNICKNAME(host, nickname) host + " 432 " + nickname + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(host, nickname) host + " 433 " + nickname + " :Nickname is already in use"
# define ERR_NOTONCHANNEL(channel) ":localhost 442 " + channel + " :You're not on that channel"
# define ERR_USERONCHANNEL(nickname, channel) ":localhost 443 " + nickname + " " + channel + " :is already on channel"
# define ERR_NOTREGISTERED(host) host + " 451 :You have not registered"
# define ERR_NEEDMOREPARAMS(host, command) host + " 461 " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(host) host + " 462 :You may not reregister"
# define ERR_PASSWDMISMATCH(host) host + " 464 :Password incorrect"
# define ERR_CHANNELISFULL(channel) ":localhost 471 " + channel + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(host, ch) host + " 472 " + ch + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(channel) ":localhost 473 " + channel + " :Cannot join channel (+i)"
# define ERR_BADCHANNELKEY(channel) ":localhost 475 " + channel + " :Cannot join channel (+k)"
# define ERR_CHANOPRIVSNEEDED(channel) ":localhost 482 " + channel + " :You're not channel operator"
# define ERR_USERSDONTMATCH(host) host + " 502 :Cant change mode for other users"
# define ERR_ERRONEUSUSER(host, user) host + " " + user + " :Erroneus user"
# define ERR_BADPASS(host) host + " :Bad Password"
# define ERR_BADMODEL(host) host + " :Bad L mode size"

# define RPL_WELCOME(user_id, nick) ":localhost 001 " + nick + " :Welcome to the Internet Relay Network " + user_id + "\r\n"
# define RPL_QUIT(user_id, reason) user_id + " QUIT :Quit: " + reason + "\r\n"
# define RPL_UMODEIS(client, mode) ":localhost 221 " + client + " " + mode + "\r\n"
# define RPL_NOTOPIC(user_id, channel) user_id + ":localhost 331 " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(user_id, channel, topic) user_id + ":localhost 332 " + channel + " :" + topic + "\r\n"
# define RPL_INVITING(channel, nickname) channel + " " + nickname + "\r\n"
# define MODE_USERMSG(client, mode) ":" + client + " MODE " + client + " :" + mode + "\r\n"
# define MODE_CHANNELMSG(channel, mode) ":" + channel + " MODE " + channel + " :" + mode + "\r\n"

#endif
