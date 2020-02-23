#include "MsgQueue.h"
#include "Logger.h"
#include "ServerSocket.h"
#include "ServerConfig.h"
#include "message.pb.h"
#include <unistd.h>

#include<thread>

void message_receiver_thread(sock::ServerSocket& ssock, config::ServerConfig& sconfig)
{
    if(ssock.create(sconfig.m_serv_addr, sconfig.serv_listn_port) && ssock.Bind() && ssock.Listen()&& ssock.init_epoll())
    {
        ssock.communicate();
    }
}

void message_sender_thread(sock::ServerSocket& ssock)
{
    ssock.send_response();
}

int main()
{
    config::ServerConfig sconfig;
    sconfig.read();
    que::MsgQueue request_queue(sconfig.m_max_num_of_msg_in_recv_que);
    que::MsgQueue resp_queue(sconfig.m_max_num_of_msg_in_send_que);
    sock::ServerSocket ssock(request_queue, resp_queue);
    std::thread msg_receiver(message_receiver_thread, std::ref(ssock), std::ref(sconfig));
    msg_receiver.detach();
    std::thread msg_sender(message_sender_thread, std::ref(ssock));
    msg_sender.detach();
    msglog::Logger logger(sconfig.m_client_msg_log_file, request_queue, resp_queue);
    logger.write();

    return 0;
}
