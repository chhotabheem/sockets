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
    int msg_id =0;
    std::string client_name("client1");
    while(k<1)
    {
        Payload pload;
        for(int i=0; i<2; ++i)
        {
            auto cdata = pload.add_data();

            cdata->set_client_msg(client_name);
            cdata->set_msg_id(++msg_id);
        }
        std::string data;
        pload.SerializeToString(&data);
        csock.Send(data);
        std::cout<< csock.Receive()<<std::endl;
        sleep(2);
        ++k;
    }
    return 0;
}
