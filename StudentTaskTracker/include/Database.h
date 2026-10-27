#pragma once
#pragma once
#include <mysql.h>

class Database {
public:
    Database();
    ~Database();

    bool connect();

private:
    MYSQL* connection;
};