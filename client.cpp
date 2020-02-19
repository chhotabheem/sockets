#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "message.pb.h"
#include<string>
#include<sys/types.h>
#include<sys/socket.h>


#include<netinet/in.h>
using namespace std;

int main()
{
    Payload pload;
    pload.set_name("Zombie");
    pload.set_id(1300000);

    int net_socket;

    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int status = connect(net_socket, (const struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if(status == -1)
    {
        printf("Not able to connect");
        return 0;
    }

//    char data[256];

    string binary;
    pload.SerializeToString(&binary);
    char data[binary.size()+1];
    strncpy(data, binary.c_str(), binary.size());
    send(net_socket, &data , sizeof(data), 0);

    recv(net_socket, &data, sizeof(data), 0);

    printf("data received is: %s", data);
    close(net_socket);
    return 0;
}
