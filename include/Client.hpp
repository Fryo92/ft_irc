#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <netinet/in.h>
# include <string>

class Client
{
	private:
		Client();

		int _socket;
		sockaddr_in _addr;

		std::string _nickName;
		std::string _userName;

	public:
		~Client();
		Client(int sock, sockaddr_in addr);

		Client & operator=(Client const & cpy);
		void	setNickName(const std::string nick) {_nickName = nick;};
		void	setUserName(const std::string user) {_userName = user;};


};


#endif