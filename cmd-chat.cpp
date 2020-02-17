#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include "Wrapper.h"

using namespace std;

int main()

{
    Wrapper::InitWinsocket();

    Wrapper* socket = new Wrapper();
    socket->CreateSocketUDP();
    socket->SetBroadcastOptions();
    socket->BindSocket();

    std::thread thread_object([socket] {while (true) socket->RecieveMsg(); });

    while (true)
    {
        std::string msg;
        cin >> msg;
        socket->SendMsg(msg);
    }

    thread_object.join();

}

