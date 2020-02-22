#ifndef LOGGER_H
#define LOGGER_H

#include<fstream>
#include<string>

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
    que::MsgQueue& m_msg_queue;
public:
    explicit Logger(std::string op_file, que::MsgQueue& queue):m_msg_queue(queue)
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
    Logger(const Logger&&) = delete;
    void write()
    {
        while(true)
        {
            std::string msg = m_msg_queue.pop();
            m_msg_file<< msg;
            m_msg_file<<std::endl;
        }
    }
};
}
#endif
