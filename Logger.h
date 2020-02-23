#ifndef LOGGER_H
#define LOGGER_H

#include<fstream>
#include<string>

#include "MsgHolder.h"

namespace que
{
class MsgQueue;
}

namespace log
{
class Logger
{
private:
    std::ofstream m_msg_file;
    que::MsgQueue& m_request_queue;
    que::MsgQueue& m_resp_queue;
public:
    explicit Logger(std::string op_file, que::MsgQueue& req_queue, que::MsgQueue& resp_queue):
        m_request_queue(req_queue),m_resp_queue(resp_queue)
    {
        m_msg_file.open(op_file, std::ios::app);
    }
    ~Logger()
    {
        m_msg_file.close();
    }
    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(const Logger&&) = delete;
    Logger(const Logger&&) = delete;
    void write()
    {
        while(true)
        {
            msgholder::MsgHolder req_msg = m_request_queue.pop();
            //m_msg_file<< msg;
            //m_msg_file<<std::endl;
            std::cout<<"SENDING RESPONSE"<<std::endl;
            std::string resp("positive ack");
            msgholder::MsgHolder res_msg(resp, req_msg.get_connection_descrip());
            m_resp_queue.push(res_msg);


        }
    }
};
}
#endif
