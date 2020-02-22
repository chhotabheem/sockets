#ifndef SOCKET_H
#define SOCKET_H

#include<string>
#include<cstring>

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netdb.h>

#include<netinet/in.h>

namespace sock
{
class Socket
{
private:
    bool m_is_server_sock = false;
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

    void Close()
    {
        if(m_socket_desc != -1)
        {
            close(m_socket_desc);
            m_socket_desc =-1;
        }
    }

public:
    explicit Socket(const int is_server_sock): m_is_server_sock(is_server_sock)
    {}
    ~Socket()
    {
        cleanup();
        Close();
    }

    Socket(const Socket& ) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&&) = delete;
    bool create(const std::string& server, const std::string& port)
    {
        struct addrinfo hints;
        int status;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        if(m_is_server_sock)
        {
            hints.ai_flags = AI_PASSIVE;
        }
        if ((status = getaddrinfo(server.c_str(), port.c_str(), &hints, &m_addr_info_list)) != 0)
        {
            //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
            //std::cout<<  "ERR: getaddrinfo: " <<  gai_strerror(status)<<std::endl;;
            return false;
        }
        for(m_addr_info = m_addr_info_list; m_addr_info != nullptr; m_addr_info = m_addr_info->ai_next)
        {
            m_socket_desc = socket(m_addr_info->ai_family, m_addr_info->ai_socktype, m_addr_info->ai_protocol);
            if(m_socket_desc == -1)
            {
                //perror("client: socket()");
                continue;
            }
            else
            {
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

    void Send(const std::string& data, int send_sock)
    {
        std::string data_size_str = std::to_string(data.size());
        auto data_size = data_size_str.size();
        std::string msg;
        while(data_size < m_prefix_msg_size)
        {
            msg.append("0");
            ++data_size;
        }
        msg += data_size_str + data;
        auto msg_sent_size = 0;
        auto msg_remaining = msg.size();
        const char* buf = msg.c_str();
        auto n =0;

        while(msg_sent_size < msg.size())
        {
            n = send(send_sock, buf+msg_sent_size, msg_remaining, 0);
            if (n == -1)
            {
                break;
            }

            msg_sent_size += n;
            msg_remaining -= n;
        }
    }

    std::string Receive(int recv_sock)
    {
        std::string data;
        char buf[1024];
        auto n = recv(recv_sock, buf, m_prefix_msg_size, 0);
        if(n != m_prefix_msg_size)
        {
            return data;
        }
        std::string msg_size_str(buf);
        auto msg_size = std::stoi(msg_size_str);
        auto size_received =0;
        while(size_received<msg_size)
        {
            n = recv(m_socket_desc, buf, sizeof(buf), 0);
            if(n<=0)
            {
                return data;
            }
            data.append(buf);
            size_received += n;
        }

        return data;
    }
};

}
#endif
