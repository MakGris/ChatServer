#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"
#include "string"

using namespace std;

class DataBase
{
public:
    DataBase();
    PGresult* select(string query);
    void processQuery(string query);


private:
    const char *conninfo;
    PGconn     *conn;
    PGresult   *res;
    int         nFields;
    int         i, j;
};

#endif // DATABASE_H
