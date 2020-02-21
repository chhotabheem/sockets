#ifndef SOCKET_H
#define SOCKET_H
namespace sock
{
class Socket
{
private:
    int m_socket_desc =-1;
    const int m_prefix_msg_size = 5;
    struct addrinfo* m_addr_info = nullptr;
    struct addrinfo* m_addr_info_list = nullptr;

    void cleanup()
    {
        if(m_addr_info_list)
        {
            freeaddrinfo(m_addr_info_list);
            m_addr_info_list = nullptr;
        }
    }

    void close()
    {
        if(m_socket_desc != -1)
        {
            close(m_socket_desc);
            m_socket_desc =-1;
        }
    }

public:
    Socket() {}
    ~Socket()
    {
        cleanup();
        close();
    }

    Socket(const Socket& ) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&&) = delete;
    bool create()
    {
        struct addrinfo hints;
        int status;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        if ((status = getaddrinfo(argv[1], NULL, &hints, &m_addr_info)) != 0)
        {
            //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
            std::cout<<  "ERR: getaddrinfo: " <<  gai_strerror(status)<<std::endl;;
            return false;
        }
        for(m_addr_info = res; m_addr_info != nullptr; m_addr_info = m_addr_info->ai_next)
        {
            m_socket_desc = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if(m_socket_desc == -1)
            {
                perror("client: socket()");
                continue;
            }
            else
            {
                m_a
                return true;
            }
        }
        return false;
    }

    const int& get_sock_descriptor() const
    {
        return m_socket_desc;
    }

    const struct addrinfo* get_socket_addr_info() const
    {
        return m_addr_info;
    }

    void send(const std::string& data)
    {
        std::string data_size_str = std::to_string(data.size());
        auto data_size = data_size_str.size();
        std::string msg;
        while(data_size < m_prefix_msg_size)
        {
            msg.append('0');
            ++data_size;
        }
        msg += msg_size_str + data;
        auto msg_sent_size = 0;
        auto msg_remaining = msg.size();
        const char* buf = msg.c_str();
        auto n =0;

        while(msg_sent_size < msg.size())
        {
            n = send(m_socket_desc, buf+msg_sent_size, msg_remaining, 0);
            if (n == -1)
            {
                break;
            }

            msg_sent_size += n;
            msg_remaining -= n;
        }
    }

    std::string receive()
    {
        std::string data;
        byte_count = recv(m_socket_desc, buf, sizeof buf, 0);
        return data;

    }
};

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
};

class ServerSocket: public Socket
{
private:
public:
    ServerSocket() {}
    ~ServerSocket() {}
    ServerSocket(const ServerSocket& ) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket(ServerSocket&&) = delete;
};
}
#endif
