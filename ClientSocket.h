#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "Socket.h"

namespace sock
{
class ClientSocket: public Socket
{
private:
public:
    ClientSocket():Socket(false)
    {}
    ~ClientSocket() {}
    ClientSocket(const ClientSocket& ) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;
    ClientSocket(ClientSocket&&) = delete;

    bool Connect()
    {
        if(connect(get_sock_descriptor(), get_socket_addr_info()->ai_addr, get_socket_addr_info()->ai_addrlen))
        {
            perror("client: connect()");
            return false;
        }
        return true;
    }

    void Send(std::string& data)
    {
        Socket::Send(data, get_sock_descriptor());

    }

    std::string Receive()
    {
        return Socket::Receive(get_sock_descriptor());
    }

};
}

#endif
