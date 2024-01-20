#include "Client.hpp"
#include "utils.hpp"

Client::Client(){

}

Client::~Client(){

}

Client::Client(int sock, sockaddr_in addr) :_socket(sock), _addr(addr), _host("localhost") {

}

Client::Client(const Client& cpy) : _nickName(cpy._nickName), _userName(cpy._userName), _pass(cpy._pass), _buf(cpy._buf){

}

Client & Client::operator=(Client const & cpy){
	if (this != &cpy){
		this->_socket = cpy._socket;
		this->_addr = cpy._addr;
	}
	return *this;
}


void	Client::setBuf(const std::string &buffer)
{
	std::istringstream iss(buffer);
    std::string token;

    while (iss >> token)
		_buf.push_back(token);
}

void	Client::setVerif(){
	_verified = true;
	// std::string str = RPL_WELCOME(user_id(_userName, _nickName), _nickName);
	// send(_socket, &str, str.size(), 0);
}