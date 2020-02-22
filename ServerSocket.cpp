#include "ServerSocket.h"
#include "message.pb.h"


int epoll_register(int events, int efd, int socket)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = socket;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, socket, &ev) == -1) {
        return 0;
    }
    return 1;
}

int main()
{
    sock::ServerSocket ssock;
    if(ssock.create("192.168.0.18", "9001") && ssock.Bind() && ssock.Listen())
    {
        int efd;
        if ((efd = epoll_create1(EPOLL_CLOEXEC))==-1) {
            fprintf(stderr, "epoll setup is failed \n");
            exit(EXIT_FAILURE);
        }
        int listen_descript;
        if (!epoll_register(EPOLLIN|EPOLLRDHUP|EPOLLET, efd, listen_descript))
        {
            fprintf(stderr, "add server socket to epoll is failed");
            exit(EXIT_FAILURE);
        }
        if(ssock.Accept())
        {
            std::string data;
            ssock.Receive();
            ssock.Send(data);
        }
    }
    return 0;
}
