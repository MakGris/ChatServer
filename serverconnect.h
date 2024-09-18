#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include "database.h"

using namespace std;

class ServerConnect
{
public:
    ServerConnect();
private:
    DataBase data;
    int sockFileDescriptor {};
    int position {};
    char buf[1024] {};
    char answerBufAuth[5] {};
    bool authentification {};
    sockaddr_in sockAddr;


    void clientConnect();
    void clientAuth(int sock);
};

#endif // SERVERCONNECT_H
