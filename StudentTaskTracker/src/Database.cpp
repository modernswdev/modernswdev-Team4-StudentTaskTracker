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
    connection = mysql_real_connect(
        connection,
        "localhost",
        "root",
        "YOUR_PASSWORD",
        "student_task_tracker",
        3306,
        nullptr,
        0
    );

    if (!connection) {
        std::cout << "Database connection failed: "
            << mysql_error(connection) << std::endl;
        return false;
    }

    std::cout << "Connected to MySQL successfully!" << std::endl;
    return true;
}