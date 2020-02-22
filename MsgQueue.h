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
    const int m_max_que_size;
public:
    explicit MsgQueue(const int max_que_size):m_max_que_size(max_que_size) {}
    ~MsgQueue() {}
    MsgQueue(const MsgQueue&) = delete;
    MsgQueue(const MsgQueue&&) = delete;
    MsgQueue& operator=(const MsgQueue&&) = delete;
    MsgQueue& operator=(const MsgQueue&) = delete;
    bool is_empty()
    {

        return m_queue.empty();
    }

    void push(std::string& msg)
    {
        std::lock_guard<std::mutex> locker(m_que_mutex);
        m_queue.push(std::move(msg));
    }

    std::string front()
    {
        std::lock_guard<std::mutex> locker(m_que_mutex);
        return m_queue.front();
    }
};
}
#endif
