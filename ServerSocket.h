#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "Socket.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include<iostream>

namespace sock
{
class ServerSocket: public Socket
{
private:
    int m_conn_descrip = -1;
    int m_epoll_id = -1;
    static const int m_max_events = 1500;
    struct epoll_event m_epoll_events[m_max_events];

    void set_to_non_blocking_mode(const int sock_id)
    {
        std::cout<<"enter: set_to_non_blocking_mode()"<<std::endl;
        int flags = fcntl (sock_id, F_GETFL, 0);
        if (flags == -1)
        {
            perror ("fcntl");
            return;
        }
        flags |= O_NONBLOCK;
        std::cout<<"set_to_non_blocking_mode(): setting sock_id:"<<sock_id<<" to flag:" <<flags<<std::endl;
        flags = fcntl (sock_id, F_SETFL, flags);
        if (flags == -1)
        {
            perror ("fcntl");
            return;
        }
        std::cout<<"exit: set_to_non_blocking_mode()"<<std::endl;
    }

public:
    ServerSocket():Socket(true) {}
    ~ServerSocket() {}
    ServerSocket(const ServerSocket& ) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket(ServerSocket&&) = delete;

    bool Bind()
    {
        std::cout<<"enter: Bind()"<<std::endl;
        if(bind(get_sock_descriptor(), get_socket_addr_info()->ai_addr, get_socket_addr_info()->ai_addrlen))
        {
            perror("Bind(): failed");
            return false;
        }
        std::cout<<"Bind(): success"<<std::endl;
        set_to_non_blocking_mode(get_sock_descriptor());
        return true;
    }

    bool Listen()
    {
        std::cout<<"enter: Listen()"<<std::endl;
        if(listen(get_sock_descriptor(), SOMAXCONN))
        {
            perror("Listen(): failed");
            return false;
        }
        std::cout<<"Listen(): success"<<std::endl;
        return true;
    }

    bool add_sock_id_for_monitoring(const int sock_id)
    {
        std::cout<<"enter: add_sock_id_for_monitoring()"<<std::endl;
        static struct epoll_event event;
        event.data.fd = sock_id;
        event.events = EPOLLIN | EPOLLET;
        if(epoll_ctl (m_epoll_id, EPOLL_CTL_ADD, sock_id, &event))
        {
            perror("add_sock_id_for_monitoring(): failed");
            return false;
        }
        std::cout<<"add_sock_id_for_monitoring(): success"<<std::endl;
        return true;
    }

    bool init_epoll()
    {
        std::cout<<"enter: init_epoll()"<<std::endl;
        m_epoll_id = epoll_create1 (0);
        if(m_epoll_id == -1)
        {
            perror("init_epoll(): failed");
            return false;
        }
        std::cout<<"init_epoll(): success"<<std::endl;
        return add_sock_id_for_monitoring(get_sock_descriptor());
    }

    bool Accept()
    {
        std::cout<<"enter: Accept()"<<std::endl;
        m_conn_descrip = accept(get_sock_descriptor(), 0, 0);
        if(m_conn_descrip == -1)
        {
            perror("Accept(): failed");
            return false;
        }
        std::cout<<"Accept(): success"<<std::endl;
        return true;
    }

    void Send(std::string& data)
    {
        std::cout<<"enter: Send()"<<std::endl;
        Socket::Send(data, m_conn_descrip);
        std::cout<<"exit: Send()"<<std::endl;

    }

    std::string Receive()
    {
        std::cout<<"enter: Receive()"<<std::endl;
        return Socket::Receive(m_conn_descrip);
    }

    bool ignore_event(struct epoll_event& event)
    {
        std::cout<<"enter: ignore_event()"<<std::endl;
        if ((event.events & EPOLLERR) ||
                (event.events & EPOLLHUP) ||
                (!(event.events & EPOLLIN)))
        {
            std::cout<<"ignore_event(): ignore and close connection"<<std::endl;
            close (event.data.fd);
            return true;
        }
        std::cout<<"ignore_event(): procced"<<std::endl;
        return false;
    }

    bool is_event_on_listner_sock_id(struct epoll_event& event)
    {
        std::cout<<"enter: is_event_on_listner_sock_id()"<<std::endl;
        if (get_sock_descriptor() == event.data.fd)
        {
            std::cout<<"is_event_on_listner_sock_id: received new connection request"<<std::endl;
            return true;
        }
        std::cout<<"exit: is_event_on_listner_sock_id()"<<std::endl;
        return false;
    }

    void handle_event_for_new_conn()
    {
        std::cout<<"enter: handle_event_for_new_conn()"<<std::endl;
        while (true)
        {
            if(!Accept())
            {
                std::cout<<"handle_event_for_new_conn: no more connections to accept"<<std::endl;
                break;
            }
            std::cout<<"new connection id is:" << m_conn_descrip<<std::endl;
            set_to_non_blocking_mode(m_conn_descrip);
            if(!add_sock_id_for_monitoring(m_conn_descrip))
            {
                perror ("epoll_ctl");
                abort ();
            }
        }
        std::cout<<"exit: handle_event_for_new_conn()"<<std::endl;
    }

    void handle_event_from_existing_conn(struct epoll_event& event)
    {
        std::cout<<"enter: handle_event_from_existing_conn()"<<std::endl;
        std::string data = Socket::Receive(event.data.fd);
        std::cout << data<<std::endl;
        if(data.empty())
        {
            std::cout<<"handle_event_from_existing_conn(): close connection"<<std::endl;
            close(event.data.fd);
        }
        std::cout<<"exit: handle_event_from_existing_conn()"<<std::endl;
    }

    void communicate()
    {
        std::cout<<"enter: communicate()"<<std::endl;
        while (true)
        {
            std::cout<<"communicate(): waiting for events"<<std::endl;
            auto num_of_evts_received = epoll_wait (m_epoll_id, m_epoll_events, m_max_events, -1);
            std::cout<<"communicate(): number of events occured:"<<num_of_evts_received<<std::endl;
            for (auto i = 0; i < num_of_evts_received; ++i)
            {
                auto& event = m_epoll_events[i];
                if(ignore_event(event))
                {
                    std::cout<<"communicate(): ignoring the event"<<std::endl;
                    continue;
                }
                if(is_event_on_listner_sock_id(event))
                {
                    std::cout<<"communicate(): handling event for new connection"<<std::endl;
                    handle_event_for_new_conn();
                }
                else
                {
                    std::cout<<"communicate(): handling event for established connection"<<std::endl;
                    handle_event_from_existing_conn(event);
                }
            }
        }

    }

};
}
#endif
