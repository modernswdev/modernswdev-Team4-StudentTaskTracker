#include "../include/Database.h"
#include <iostream>

Database::Database() {
    connection = mysql_init(nullptr);
}

Database::~Database() {
    if (connection) {
        mysql_close(connection);
    }
}

bool Database::connect() {
    if (mysql_options(connection, MYSQL_READ_DEFAULT_GROUP, "client") != 0) {
        std::cout << "MySQL client configuration failed: "
            << mysql_error(connection) << std::endl;
        return false;
    }

    if (!mysql_real_connect(
        connection,
        "127.0.0.1",
        nullptr,
        nullptr,
        "student_task_tracker",
        3306,
        nullptr,
        0
    )) {
        std::cout << "Database connection failed: "
            << mysql_error(connection) << std::endl;
        return false;
    }

    std::cout << "Connected to MySQL successfully!" << std::endl;
    return true;
}