#include "ClientSocket.h"
#include "message.pb.h"

int main()
{
    sock::ClientSocket csock;
    if(csock.create("192.168.0.18", "9001") && csock.Connect())
    {
        return 0;
    }

    Payload pload;
    pload.set_name("Zombie");
    pload.set_id(1300000);
    std::string data;
    pload.SerializeToString(&data);
    csock.Send(data);
    return 0;
}
