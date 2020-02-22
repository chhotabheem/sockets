#include "ServerSocket.h"
#include "message.pb.h"

int main()
{
    sock::ServerSocket ssock;
    if(ssock.create("192.168.0.18", "9001") && ssock.Bind() && ssock.Listen()&& init_epoll())
    {
        sscok.communicate();
        if(ssock.Accept())
        {
            std::string data;
            ssock.Receive();
            ssock.Send(data);
        }
    }
    return 0;
}
