#include "MsgQueue.h"
#include "Logger.h"
#include "ServerSocket.h"
#include "message.pb.h"
#include <unistd.h>

#include<thread>

void message_receiver_thread(sock::ServerSocket& ssock)
{
    if(ssock.create("192.168.0.18", "9001") && ssock.Bind() && ssock.Listen()&& ssock.init_epoll())
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
    que::MsgQueue request_queue(100);
    que::MsgQueue resp_queue(100);
    sock::ServerSocket ssock(request_queue, resp_queue);
    std::thread msg_receiver(message_receiver_thread, std::ref(ssock));
    msg_receiver.detach();
    std::thread msg_sender(message_sender_thread, std::ref(ssock));
    msg_sender.detach();
    log::Logger logger("client_messages.txt", request_queue, resp_queue);
    logger.write();

    return 0;
}
