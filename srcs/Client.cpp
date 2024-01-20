#include "Client.hpp"

Client::Client(){

}

Client::~Client(){

}

Client::Client(int sock, sockaddr_in addr) : _socket(sock), _addr(addr) {

}

Client & Client::operator=(Client const & cpy){
	if (this != &cpy){
		this->_socket = cpy._socket;
		this->_addr = cpy._addr;
	}
	return *this;
}


void	Client::setBuf(const std::string buffer)
{
	std::istringstream iss(buffer);
    std::string token;

    while (iss >> token)
		_buf.push_back(token);
}