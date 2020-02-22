#include "ServerSocket.h"
#include "message.pb.h"

int main()
{
    sock::ServerSocket ssock;
    if(ssock.create("192.168.0.18", "9001") && ssock.Bind() && ssock.Listen()&& ssock.init_epoll())
    {
        ssock.communicate();
    }
    return 0;
}
