#ifndef CONNECTION_ID_SET_H
#define CONNECTION_ID_SET_H
#include<mutex>
#include<unordered_set>
namespace connset
{
class ConnIdSet
{
private:
    std::unordered_set<int> m_conn_id_set;
    std::mutex m_conn_set_mutex;
public:
    void add_conn_descrip(const int conn_id)
    {
        std::unique_lock<std::mutex> locker(m_conn_set_mutex);
        m_conn_id_set.insert(conn_id);
    }

    void remove_conn_descrip(const int conn_id)
    {
        std::unique_lock<std::mutex> locker(m_conn_set_mutex);
        if(m_conn_id_set.find(conn_id) != m_conn_id_set.end())
        {
            m_conn_id_set.erase(conn_id);
        }
    }
    bool is_connection_up(const int conn_id)
    {
        std::unique_lock<std::mutex> locker(m_conn_set_mutex);
        if(m_conn_id_set.find(conn_id) != m_conn_id_set.end())
        {
            return true;
        }
        return false;
    }
};

}
#endif
