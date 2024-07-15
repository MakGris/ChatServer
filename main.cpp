#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>


using namespace std;

int main()
{
    int sockFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFileDescriptor == -1) {
        cout << "Failed to create socket" << endl;
        exit(EXIT_FAILURE);
    }
    sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(9999);
    if(bind(sockFileDescriptor, (struct sockaddr*)&sockAddr, sizeof(sockAddr))  < 0) {
        cout << "Failed to bind port: 9999" << endl;
    }
    if(listen(sockFileDescriptor, 20) < 0) {
        cout << "Failed to listen" << endl;
    }
    return 0;
}
