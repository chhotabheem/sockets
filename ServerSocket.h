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

    bool init_epoll()
    {
        m_epoll_id = epoll_create1 (0);
        if(m_epoll_id == -1)
        {
            return false;
        }
        struct epoll_event event;
        event.data.fd = get_sock_descriptor();
        event.events = EPOLLIN | EPOLLET;
        if(epoll_ctl (m_epoll_id, EPOLL_CTL_ADD, get_sock_descriptor(), &event))
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

    bool ignore_event(const int i)
    {
        if ((m_epoll_events[i].events & EPOLLERR) ||
                (m_epoll_events[i].events & EPOLLHUP) ||
                (!(m_epoll_events[i].events & EPOLLIN)))
        {
            close (m_epoll_events[i].data.fd);
            return true;
        }
        return false;
    }

    bool is_event_on_listner_sock_id(const int i)
    {
        if (get_sock_descriptor() == m_epoll_events[i].data.fd)
        {
            return true;
        }
        return false;
    }

    void handle_event_for_new_conn()
    {

        /* We have a notification on the listening socket, which
           means one or more incoming connections. */
        while (1)
        {
            struct sockaddr in_addr;
            socklen_t in_len;
            int infd;
            char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

            in_len = sizeof in_addr;
            infd = accept (sfd, &in_addr, &in_len); // create new socket fd from pending listening socket queue
            if (infd == -1) // error
            {
                if ((errno == EAGAIN) ||
                        (errno == EWOULDBLOCK))
                {
                    /* We have processed all incoming connections. */
                    break;
                }
                else
                {
                    perror ("accept");
                    break;
                }
            }

            int optval = 1;
            setsockopt(infd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));  // set socket for port reuse

            /* get the client's IP addr and port num */
            s = getnameinfo (&in_addr, in_len,
                             hbuf, sizeof hbuf,
                             sbuf, sizeof sbuf,
                             NI_NUMERICHOST | NI_NUMERICSERV);
            if (s == 0)
            {
                printf("Accepted connection on descriptor %d "
                       "(host=%s, port=%s)\n", infd, hbuf, sbuf);
            }

            /* Make the incoming socket non-blocking and add it to the
               list of fds to monitor. */
            int flags = fcntl (infd, F_GETFL, 0);
            flags |= O_NONBLOCK;
            fcntl (infd, F_SETFL, flags);

            event.data.fd = infd;
            event.events = EPOLLIN | EPOLLET;

            s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
            if (s == -1)
            {
                perror ("epoll_ctl");
                abort ();
            }
            clientMap[event.data.fd]=0;  // init msg counter
        }
        continue;
    }

    void handle_event_from_existing_conn()
    {

        /* We have data on the fd waiting to be read. Read and
           display it. We must read whatever data is available
           completely, as we are running in edge-triggered mode
           and won't get a notification again for the same
           data. */
        int done = 0;

        while (1)
        {
            ssize_t count;
            char buf[BUFFERSIZE];

            count = read (events[i].data.fd, buf, sizeof buf);

            if (count == -1)
            {
                /* If errno == EAGAIN, that means we have read all
                   data. So go back to the main loop. */
                if (errno != EAGAIN)
                {
                    perror ("read");
                    done = 1;
                }
                break;
            }
            else if (count == 0)
            {
                /* End of file. The remote has closed the
                   connection. */
                done = 1;
                break;
            }

            buf[count]=0;
            char wbuf[BUFFERSIZE];
            int cx=snprintf(wbuf,BUFFERSIZE,"(fd:%d seq:%d) %s",events[i].data.fd, clientMap[events[i].data.fd],buf);

            /* Write the buffer to standard output */
            s = write (1, wbuf, cx);
            if (s == -1)
            {
                perror ("write");
                abort ();
            }
        }

        if (done)
        {
            printf ("Closed connection on descriptor %d\n",
                    events[i].data.fd);

            /* Closing the descriptor will make epoll remove it
               from the set of descriptors which are monitored. */
            close (events[i].data.fd);
        }
    }
    void communicate()
    {
        while (true)
        {
            auto evts_received = epoll_wait (m_epoll_id, m_epoll_events, m_max_events, -1);
            for (auto i = 0; i < evts_received; ++i)
            {
                if(ignore_event(i))
                {
                    continue;
                }
                if(is_event_on_listner_sock_id(i))
                {
                    handle_event_for_new_conn();
                }
                else
                {
                    handle_event_from_existing_conn();
                }
            }
        }

    }

};
}
#endif
