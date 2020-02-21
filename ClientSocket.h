#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
namespace sock
{
class ClientSocket: public Socket
{
private:
public:
    ClientSocket() {}
    ~ClientSocket() {}
    ClientSocket(const ClientSocket& ) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;
    ClientSocket(ClientSocket&&) = delete;

    bool connect()
    {
        if(connect(get_sock_descriptor(), get_sock_descriptor()->ai_addr, get_sock_descriptor()->ai_addrlen))
        {
            perror("client: connect()");
            return false;
        }
        return true;
    }

    void send(std::string& data)
    {
        send(get_sock_descriptor(), data);

    }

    std::string receive()
    {
        return receive(get_sock_descriptor());
    }

};
}

#endif
