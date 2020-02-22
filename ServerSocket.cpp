#include "MsgQueue.h"
#include "Logger.h"
#include "ServerSocket.h"
#include "message.pb.h"
#include <unistd.h>

#include<thread>

void message_receiver_thread(que::MsgQueue& queue)
{
    sock::ServerSocket ssock(queue);
    if(ssock.create("192.168.0.18", "9001") && ssock.Bind() && ssock.Listen()&& ssock.init_epoll())
    {
        ssock.communicate();
    }
}

int main()
{
    que::MsgQueue queue(100);
    std::thread msg_receiver(message_receiver_thread, std::ref(queue));
    msg_receiver.detach();
    log::Logger logger("client_messages.txt", queue);
    logger.write();

    return 0;
}
