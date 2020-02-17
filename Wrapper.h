#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define MYPORT 23656   

class Wrapper 
{
public:
    bool static InitWinsocket();
    bool CreateSocketUDP();
    bool SetBroadcastOptions();
    bool BindSocket();
    bool SendMsg(std::string);
    void RecieveMsg();

private:
    SOCKET m_Socket;

    struct sockaddr_in Recv_addr;
    struct sockaddr_in Sender_addr;

};