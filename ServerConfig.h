#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include<string>
#include<fstream>
#include "json.hpp"

namespace config
{
struct ServerConfig
{
    std::string m_serv_addr;
    std::string serv_listn_port;
    int m_max_num_of_msg_in_recv_que;
    int m_max_num_of_msg_in_send_que;
    std::string m_client_msg_log_file;

    void read()
    {
        std::ifstream serv_addr_buffer("server_address_config.json");
        nlohmann::json serv_addr_json;
        serv_addr_buffer >> serv_addr_json;

        m_serv_addr = serv_addr_json["ServerAddress"];
        serv_listn_port = serv_addr_json["ServerListeningPort"];

        std::ifstream server_config_buffer("server_config.json");
        nlohmann::json server_json;
        server_config_buffer >> server_json;

        m_client_msg_log_file = server_json["ClientMessagesLogFile"];
        std::string field = server_json["MaxNumberOfMsgsInReceiveQueue"];
        m_max_num_of_msg_in_recv_que = std::stoi(field);
        field = server_json["MaxNumberOfMsgsInSendQueue"];
        m_max_num_of_msg_in_send_que = std::stoi(field);
    }
};
}
#endif
