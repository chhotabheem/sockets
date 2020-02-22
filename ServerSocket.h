#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "Socket.h"

namespace sock
{
class ServerSocket: public Socket
{
private:
    int m_conn_descrip = -1;
public:
    ServerSocket() {}
    ~ServerSocket() {}
    ServerSocket(const ServerSocket& ) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket(ServerSocket&&) = delete;

    bool Bind()
    {
        if(bind(get_sock_descriptor(), get_socket_addr_info()->ai_addr, get_socket_addr_info()->ai_addrlen))
        {
            return false;
        }
        return true;
    }

    bool Listen()
    {
        if(listen(get_sock_descriptor(), 128))
        {
            return false;
        }
        return true;
    }

    bool Accept()
    {
        m_conn_descrip = accept(get_sock_descriptor(), 0, 0);
        if(m_conn_descrip == -1)
        {
            return false;
        }
        return true;
    }

    void Send(std::string& data)
    {
        Socket::Send(data, m_conn_descrip);

    }

    std::string Receive()
    {
        return Socket::Receive(m_conn_descrip);
    }

};
}
#endif
