#ifndef LOGGER_H
#define LOGGER_H
namespace que
{
class MsgQueue;
}
namespace log
{
class Logger
{
private:
    que::MsgQueue& m_msg_queue;
public:
    explicit Logger(que::MsgQueue& queue):m_msg_queue(queue)
    {}
    ~Logger() {};
    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&&) = delete;
    void write()
    {

    }


};
}
#endif
