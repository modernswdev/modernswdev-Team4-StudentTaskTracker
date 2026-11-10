#include "../include/Database.h"
#include <iostream>
#include <cstdlib>

Database::Database() {
    connection = mysql_init(nullptr);
}

Database::~Database() {
    if (connection) {
        mysql_close(connection);
    }
}

bool Database::connect() {
    my_bool verify_server_cert = 0;
    mysql_options(connection, MYSQL_OPT_SSL_VERIFY_SERVER_CERT,
              &verify_server_cert);

    const char* host = std::getenv("MYSQL_HOST");
    const char* user = std::getenv("MYSQL_USER");
    const char* password = std::getenv("MYSQL_PASSWORD");
    const char* database = std::getenv("MYSQL_DATABASE");

    if (!host) host = "mysql";
    if (!user) user = "tracker";
    if (!password) password = "tracker_password";
    if (!database) database = "student_task_tracker";

    if (!mysql_real_connect(
        connection,
        host,
        user,
        password,
        database,
        3306,
        nullptr,
        0
    )) {
        std::cerr << "Database connection failed: "
                  << mysql_error(connection) << std::endl;
        return false;
    }

    std::cout << "Connected to MySQL successfully!" << std::endl;
    return true;
}
