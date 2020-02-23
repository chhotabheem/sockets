#include "ClientSocket.h"
#include "ClientConfig.h"
#include "message.pb.h"
#include <unistd.h>

int main()
{
    config::ClientConfig cconfig;
    cconfig.read();
    sock::ClientSocket csock;
    if(!csock.create(cconfig.m_serv_addr, cconfig.serv_listn_port) || !csock.Connect())
    {
        return 0;
    }
    auto num_of_msgs_sent =0;
    auto msg_id =0;
    while(num_of_msgs_sent < cconfig.m_total_num_msg_to_send)
    {
        Payload pload;
        for(auto i=0; i<cconfig.m_num_of_obj_in_each_msg; ++i)
        {
            auto cdata = pload.add_data();

            cdata->set_client_msg(cconfig.m_client_name);
            cdata->set_msg_id(++msg_id);
        }
        std::string data;
        pload.SerializeToString(&data);
        csock.Send(data);
        std::cout<< csock.Receive()<<std::endl;
        sleep(cconfig.m_time_intv_bw_msg_sec);
        ++num_of_msgs_sent;
    }
    return 0;
}
