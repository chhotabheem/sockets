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
    std::condition_variable m_con_var;
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
        std::unique_lock<std::mutex> locker(m_que_mutex);
        if(m_queue.size() < m_max_que_size)
        {
            m_queue.push(std::move(msg));
            locker.unlock();
            m_con_var.notify_one();
        }
        else
        {
            std::cout<<"push(): ERR queue is full. dropping the message"<<std::endl;
        }
    }

    std::string front()
    {
        std::unique_lock<std::mutex> locker(m_que_mutex);
        m_con_var.wait(locker, [&]() {
            return !m_queue.empty();
        });
        std::string msg = m_queue.front();
        m_queue.pop();
        return msg;
    }
};
}
#endif
