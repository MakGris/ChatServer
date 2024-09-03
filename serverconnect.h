#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <string>

using namespace std;

class ServerConnect
{
public:
    ServerConnect();
private:
    int sockFileDescriptor {};
    char buf[1024] {};
    char answerBufAuth[5] {};
    string login {};

};

#endif // SERVERCONNECT_H
