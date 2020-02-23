#ifndef LOGGER_H
#define LOGGER_H

#include "MsgHolder.h"
#include "message.pb.h"

#include<fstream>
#include<string>
#include<iostream>
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
            Payload pload;
            std::string resp;

            if(!pload.ParseFromString(req_msg.get_data()))
            {
                resp = "ACK fail";
            }
            else
            {
                for (auto& data:pload.data())
                {
                    m_msg_file<< "message from client:" << data.client_msg()<< " with msg id:"<< data.msg_id();
                    m_msg_file<<std::endl;
                }
                resp = "ACK success";
            }

            msgholder::MsgHolder res_msg(resp, req_msg.get_connection_descrip());
            m_resp_queue.push(res_msg);


        }
    }
};
}
#endif
