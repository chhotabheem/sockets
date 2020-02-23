#ifndef MSGHOLDER_H
#define MSGHOLDER_H

#include<string>

namespace msgholder
{
class MsgHolder
{
private:
    std::string m_serialized_data;
    int m_conn_descrip =-1;
public:
    explicit MsgHolder(std::string data, int conn_descrip):m_serialized_data(data), m_conn_descrip(conn_descrip)
    {}
    ~MsgHolder() {}
    //MsgHolder(const MsgHolder&)=delete;
    //MsgHolder(const MsgHolder&&)=delete;
    //MsgHolder& operator=(const MsgHolder&)=delete;
    //MsgHolder& operator=(const MsgHolder&&)=delete;
    std::string get_data()
    {
        return m_serialized_data;
    }
    int get_connection_descrip()
    {
        return m_conn_descrip;
    }
};
}
#endif
