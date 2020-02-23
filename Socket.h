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

#include<iostream>

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
        std::cout<<"enter: cleanup()"<<std::endl;
        if(m_addr_info_list)
        {
            std::cout<<"cleanup(): delete address info list"<<std::endl;
            freeaddrinfo(m_addr_info_list);
            m_addr_info_list = nullptr;
        }
        std::cout<<"exit: cleanup()"<<std::endl;
    }

    void Close()
    {
        std::cout<<"enter: Close()"<<std::endl;
        if(m_socket_desc != -1)
        {
            std::cout<<"Close(): close socket descriptor"<<std::endl;
            close(m_socket_desc);
            m_socket_desc =-1;
        }
        std::cout<<"exit: Close()"<<std::endl;
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
        std::cout<<"enter: create()"<<std::endl;
        struct addrinfo hints;
        int status;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        if(m_is_server_sock)
        {
            std::cout<<"create(): set ai flags for server socket"<<std::endl;
            hints.ai_flags = AI_PASSIVE;
        }
        if ((status = getaddrinfo(server.c_str(), port.c_str(), &hints, &m_addr_info_list)) != 0)
        {
            perror("create(): getaddrinfo() failed");
            //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
            //std::cout<<  "ERR: getaddrinfo: " <<  gai_strerror(status)<<std::endl;;
            return false;
        }
        std::cout<<"create(): getaddrinfo() success"<<std::endl;
        for(m_addr_info = m_addr_info_list; m_addr_info != nullptr; m_addr_info = m_addr_info->ai_next)
        {
            std::cout<<""<<std::endl;
            m_socket_desc = socket(m_addr_info->ai_family, m_addr_info->ai_socktype, m_addr_info->ai_protocol);
            if(m_socket_desc == -1)
            {
                perror("create(): socket() failed");
                continue;
            }
            else
            {
                std::cout<<"create(): socket() success"<<std::endl;
                return true;
            }
        }
        std::cout<<"create(): all socket() calls failed"<<std::endl;
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
        //std::cout<<"enter: Send()"<<std::endl;
        //std::cout<<"Send(): data to be sent:"<<data<<std::endl;

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

        //std::cout<<"Send(): message to be sent:"<<msg<<std::endl;
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
        //std::cout<<"exit: Send()"<<std::endl;
    }

    std::string Receive(int recv_sock)
    {
        std::cout<<"enter: Receive()"<<std::endl;
        std::string data;
        char buf[1024];

        auto n = recv(recv_sock, buf, m_prefix_msg_size, 0);
        if(n != m_prefix_msg_size)
        {
            return data;
        }
        buf[n] ='\0';
        std::string msg_size_str(buf);
        auto msg_size = std::stoi(msg_size_str);
        auto size_received =m_prefix_msg_size;
        while(size_received<msg_size)
        {
            n = recv(recv_sock, buf, sizeof(buf), 0);
            if(n<=0)
            {
                return data;
            }
            buf[n]='\0';
            data.append(buf);
            size_received += n;
        }
        std::cout<<"exit: Receive()"<< std::endl;

        return data;
    }
};

}
#endif
