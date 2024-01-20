#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sstream>
# include <vector>
# include <netinet/in.h>
# include <string>
# include <stdexcept>

class Client
{
	private:
		Client();

		int _socket;
		sockaddr_in _addr;

		std::string _nickName;
		std::string _userName;
		std::string _pass;
		std::vector<std::string>	_buf;

		// bool _verified;

	public:
		~Client();
		Client(int sock, sockaddr_in addr);

		Client & operator=(Client const & cpy);

		int			getSocket() {return _socket;};
		std::string	getNickName() {return _nickName;};
		std::string	getUserName() {return _userName;};
		std::string	getPass() {return _pass;};
		std::vector<std::string>	getBuf() {return _buf;};


		void	setNickName(const std::string nick) {_nickName = nick;};
		void	setUserName(const std::string user) {_userName = user;};
		void	setPass(const std::string pass) {_pass = pass;};
		void	setBuf(const std::string buffer);



};


#endif