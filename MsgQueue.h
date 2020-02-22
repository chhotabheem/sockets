#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include<queue>
#include<mutex>
#include<condition_variable>
#include<string>

namespace que
{
class MsgQueue
{
private:
    std::queue<std::string>  m_queue;
    std::mutex m_que_mutex;
public:
    bool is_empty()
    {
        return m_queue.empty();
    }

    void push(std::string& msg)
    {
        m_queue.push(std::move(msg));
    }

    std::string front()
    {
        return m_queue.front();
    }
};
}
#endif
