#ifndef SOCKET_H
#define SOCKET_H
namespace sock
{
class ServerSocket: public Socket
{
private:
public:
    ServerSocket() {}
    ~ServerSocket() {}
    ServerSocket(const ServerSocket& ) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket(ServerSocket&&) = delete;

    bool bind()
    {
    }

    bool listen()
    {
    }

    bool accept()
    {
    }

    void send(std::string& data)
    {
        send(conn_id, data);

    }

    std::string receive()
    {
        return receive(conn_id);
    }

};
}
#endif
