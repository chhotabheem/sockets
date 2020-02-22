#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "Socket.h"
#include <sys/epoll.h>
#include <fcntl.h>

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
        int flags = fcntl (sock_id, F_GETFL, 0);
        flags |= O_NONBLOCK;
        fcntl (sock_id, F_SETFL, flags);
    }

public:
    ServerSocket():Socket(true) {}
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
        if(listen(get_sock_descriptor(), SOMAXCONN))
        {
            return false;
        }
        return true;
    }

    bool add_sock_id_for_monitoring(const int sock_id)
    {

        struct epoll_event event;
        event.data.fd = sock_id;
        event.events = EPOLLIN | EPOLLET;
        if(epoll_ctl (m_epoll_id, EPOLL_CTL_ADD, sock_id, &event))
        {
            return false;
        }
        return true;
    }

    bool init_epoll()
    {
        m_epoll_id = epoll_create1 (0);
        if(m_epoll_id == -1)
        {
            return false;
        }
        return add_sock_id_for_monitoring(get_sock_descriptor());
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

    bool ignore_event(struct epoll_event& event)
    {
        if ((event.events & EPOLLERR) ||
                (event.events & EPOLLHUP) ||
                (!(event.events & EPOLLIN)))
        {
            close (event.data.fd);
            return true;
        }
        return false;
    }

    bool is_event_on_listner_sock_id(struct epoll_event& event)
    {
        if (get_sock_descriptor() == event.data.fd)
        {
            return true;
        }
        return false;
    }

    void handle_event_for_new_conn()
    {
        while (true)
        {
            if(!Accept())
            {
                break;
            }
            set_to_non_blocking_mode(m_conn_descrip);
            if(!add_sock_id_for_monitoring(m_conn_descrip))
            {
                perror ("epoll_ctl");
                abort ();
            }
        }
    }

    void handle_event_from_existing_conn(struct epoll_event& event)
    {

        Socket::Receive(event.data.fd);
        close (event.data.fd);
    }

    void communicate()
    {
        while (true)
        {
            auto num_of_evts_received = epoll_wait (m_epoll_id, m_epoll_events, m_max_events, -1);
            for (auto i = 0; i < num_of_evts_received; ++i)
            {
                auto& event = m_epoll_events[i];
                if(ignore_event(event))
                {
                    continue;
                }
                if(is_event_on_listner_sock_id(event))
                {
                    handle_event_for_new_conn();
                }
                else
                {
                    handle_event_from_existing_conn(event);
                }
            }
        }

    }

};
}
#endif
