#include "Wrapper.h"

bool Wrapper::InitWinsocket()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Server: WSAStartup failed with error: " << WSAGetLastError() << endl;
        return false;
    }

    return true;
}

bool Wrapper::CreateSocketUDP()
{
    m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (m_Socket == INVALID_SOCKET)
    {
        cout << "Server: Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return false;
    }

    return true;
}

bool Wrapper::SetBroadcastOptions()
{
    char broadcast = '1';
    if (setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    {
        cout << "Error in setting Broadcast option" << endl;
        closesocket(m_Socket);
        return false;
    }

    return true;
}

bool Wrapper::BindSocket()
{
    Recv_addr.sin_family = AF_INET;
    Recv_addr.sin_port = htons(MYPORT);
    Recv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_Socket, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
    {
        cout << "Error in BINDING" << WSAGetLastError();
        closesocket(m_Socket);
        return false;
    }

    return true;
}

bool Wrapper::SendMsg(std::string msg)
{
    Sender_addr.sin_family = AF_INET;
    Sender_addr.sin_port = htons(MYPORT);
    Sender_addr.sin_addr.s_addr = INADDR_BROADCAST;

    int structLength = sizeof(struct sockaddr_in);
    if (sendto(m_Socket, msg.c_str(), strlen(msg.c_str()) + 1, 0, (sockaddr*)&Sender_addr, structLength) < 0)
    {
        cout << "sendto Error" << WSAGetLastError() << endl;
    }
    return false;
}

void Wrapper::RecieveMsg()
{
    int len1 = sizeof(struct sockaddr_in);
    char recvbuff1[50];
    int recvbufflen1 = 50;


    if (recv(m_Socket, recvbuff1, recvbufflen1, 0) < 0)
    {
        cout << "\n\n\tFAIL : " << recvbuff1;
    }

    sockaddr_in name;
    int n_l = sizeof(name);
    ZeroMemory(&name, sizeof(name));
    if (getsockname(m_Socket, (sockaddr*)&name, &n_l) < 0)
    {
        cout << endl << "getsockname ERROR" << endl;
    }
    else
    {
        cout << " (" << inet_ntoa((in_addr)name.sin_addr);
        cout << ":" << ntohs(name.sin_port) << "):  ";
        cout << recvbuff1 << endl;
    }
}

