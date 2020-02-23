#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include<string>
#include<fstream>
#include "json.hpp"

namespace config
{
struct ClientConfig
{
    std::string m_serv_addr;
    std::string serv_listn_port;
    std::string m_client_name;
    int m_num_of_obj_in_each_msg;
    int m_total_num_msg_to_send;
    int m_time_intv_bw_msg_sec;

    void read()
    {

        std::ifstream serv_addr_buffer("server_address_config.json");
        nlohmann::json serv_addr_json;
        serv_addr_buffer >> serv_addr_json;

        m_serv_addr = serv_addr_json["ServerAddress"];
        serv_listn_port = serv_addr_json["ServerListeningPort"];

        std::ifstream client_config_buffer("client_config.json");
        nlohmann::json client_json;
        client_config_buffer >> client_json;

        m_client_name = client_json["ClientName"];
        std::string field = client_json["NumberOfObjectsInEachMsg"];
        m_num_of_obj_in_each_msg = std::stoi(field);
        field = client_json["TotalNumberOfMsgsToBeSent"];
        m_total_num_msg_to_send = std::stoi(field);
        field = client_json["TimeIntervalBwMsgsInSec"];
        m_time_intv_bw_msg_sec = std::stoi(field);
    }
};
}
#endif
