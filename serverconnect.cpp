#include "serverconnect.h"

#include <cstring>

ServerConnect::ServerConnect()
{

    PGresult *res = data.select("select * from newtable");
    cout << "Запрос выполнен " << PQntuples(res) << PQnfields(res) <<  endl;
    for (int i = 0; i < PQntuples(res); i++)
    {
        cout << "Читаем строку " << endl;
        for (int j = 0; j < PQnfields(res); j++){
            cout << "Читаем столбец " << PQgetvalue(res, i, j) <<  endl;
        }
        //     printf("%-15s", PQgetvalue(res, i, j));
        // printf("\n");
    }




    sockFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFileDescriptor == -1) {
        cout << "Failed to create socket" << endl;
        exit(EXIT_FAILURE);
    }
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(9999);
    if(bind(sockFileDescriptor, (struct sockaddr*)&sockAddr, sizeof(sockAddr))  < 0) {
        cout << "Failed to bind port: 9999" << endl;
    }
    if(listen(sockFileDescriptor, 20) < 0) {
        cout << "Failed to listen" << endl;
    }
    clientConnect();
}

void ServerConnect::clientConnect() {
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

            memcpy(&packType, buf, 4);
            position += 4;
            if(packType == 0) {
                clientAuth(sock);
            }




        }
    }
}
void ServerConnect::clientAuth(int sock) {
    int loginLenght {};

    int packType = 0;
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
    PGresult *res = data.select("select * from auth where login = '" + string (loginTmp) + "' and _password = '" + string (passwordTemp)+"'");
    cout << "select * from auth where login = '" + string (loginTmp) + "' and _password = '" + string (passwordTemp)+"'" << endl;
    if (PQntuples(res)) {
        cout << "authentification complete" << endl;
    } else {
        cout << "authentification false" << endl;
    }
    // if(*loginTmp == *login && *passwordTemp == *password) {
    //     authentification = true;
    //     cout << "Auth true" << endl;
    // } else {
    //     authentification = false;
    //     cout << "Auth false" << endl;
    // }
    memcpy(answerBufAuth, &packType, 4);
    memcpy(&answerBufAuth[4], &authentification, 1);
    send(sock, answerBufAuth, 5, 0);
    close(sock);
    cout << "packType: " << packType << " " <<"Login lenght: " << loginLenght << " " << "Login: " << loginTmp << "Password lenght: " << passwordLenght << "Password: " << passwordTemp << endl;

}
