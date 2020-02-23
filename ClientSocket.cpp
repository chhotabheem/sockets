#include "ClientSocket.h"
#include "message.pb.h"
#include <unistd.h>
int main()
{
    sock::ClientSocket csock;
    if(!csock.create("192.168.0.18", "9001") || !csock.Connect())
    {
        return 0;
    }
    int k =0;
    while(k<5)
    {
        Payload pload;
        pload.set_name("Zombie");
        pload.set_id(1300000);
        std::string data("hello server");
        //pload.SerializeToString(&data);
        csock.Send(data);
        std::cout<< csock.Receive()<<std::endl;
        sleep(2);
        ++k;
    }
    return 0;
}
