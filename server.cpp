#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "message.pb.h"

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<string>
#include<iostream>
using namespace std;

int main()
{
    char msg[256] = "msg from my server";
    int serv_sock;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(serv_sock, 5);
    char data[256];
    int client_sock = accept(serv_sock, 0, 0);
    recv(client_sock, &data, sizeof(data), 0);
    string binary(data);
    Payload pload;
cout<<"before parsing"<<endl;
    pload.ParseFromString(binary);
cout<<"after parsing"<<endl;
    cout<<pload.name()<<endl;
    cout<<pload.id()<<endl;
    send(client_sock, msg, sizeof(msg), 0);
    close(serv_sock);
    return 0;
}
