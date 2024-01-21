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
		int _socket;
		sockaddr_in _addr;

		std::string _nickName;
		std::string _userName;
		std::string _host;
		std::string _pass;
		std::string _rpl;
		std::vector<std::string>	_buf;

		bool _invisible;
		bool _irssi;
		bool _verified;
		bool _deco;

	public:
		Client();
		Client(const Client& cpy);
		~Client();
		Client(int sock, sockaddr_in addr);

		Client & operator=(Client const & cpy);

		int			getSocket() {return _socket;};
		std::string	&getNickName() {return _nickName;};
		std::string	&getUserName() {return _userName;};
		std::string	&getPass() {return _pass;};
		std::string &getHost() {return _host;};
		std::string &getRpl() {return _rpl;};
		bool		getMode() {return _invisible;};
		bool		getVerif() {return _verified;};
		bool		getIrssi() {return _irssi;};
		bool		getDeco() {return _deco;};
		std::vector<std::string>	&getBuf() {return _buf;};


		void	setNickName(const std::string &nick) {_nickName = nick;};
		void	setUserName(const std::string &user) {_userName = user;};
		void	setPass(const std::string &pass) {_pass = pass;};
		void	setRpl(const std::string &rpl) {_rpl = rpl;};
		void	setMode(bool i) {_invisible = i;};
		void	setVerif();
		void	setDeco() {_deco = true;};
		void	setIrssi() {_irssi = true;};
		void	setBuf(const std::string &buffer);


};

#endif