#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
    int sockFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    char buf[1024];
    char answerBufAuth[5];
    const char login [6] = {'M','a','k','s','i','m'};
    const char password [5] = {'1', '2', '3', '4', '5'};
    bool authentification {};

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

    while (true) {
        int sock = accept(sockFileDescriptor, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        while(true)
        {
            int bytes_read = recv(sock, buf, 1024, 0);

            if(bytes_read <= 0) break;
            int packType {};
            int position {};
            memcpy(&packType, buf, 4);
            position += 4;
            if(packType == 0) {
                int loginLenght {};
                memcpy(&loginLenght, &buf[position],4);
                position += 4;
                char* loginTmp = new char(loginLenght);
                memcpy(loginTmp, &buf[position], loginLenght);
                position += loginLenght;
                int passwordLenght {};
                memcpy(&passwordLenght, &buf[position], 4);
                position += 4;
                char* passwordTemp = new char(passwordLenght);
                memcpy(passwordTemp, &buf[position], passwordLenght);
                if(*loginTmp == *login && *passwordTemp == *password) {
                    authentification = true;
                    cout << "Auth true" << endl;
                } else {
                    authentification = false;
                    cout << "Auth false" << endl;
                }
                memcpy(answerBufAuth, &packType, 4);
                memcpy(&answerBufAuth[4], &authentification, 1);
                send(sock, answerBufAuth, 5, 0);
                close(sock);
                cout << "packType: " << packType << " " <<"Login lenght: " << loginLenght << " " << "Login: " << loginTmp << "Password lenght: " << passwordLenght << "Password: " << passwordTemp << endl;
            }




        }
    }
    cout << "Новое подключение" << endl;
    return 0;
}
