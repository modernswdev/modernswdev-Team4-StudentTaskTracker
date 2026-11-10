
#include "../include/Database.h"
#include <iostream>
#include <cstdlib>
#include <string>

std::string getEnv(const char* name, const char* fallback)
{
#ifdef _WIN32
    char* value = nullptr;
    size_t size = 0;

    if (_dupenv_s(&value, &size, name) == 0 && value != nullptr)
    {
        std::string result(value);
        std::free(value);
        return result;
    }
#else
    const char* value = std::getenv(name);

    if (value != nullptr)
    {
        return value;
    }
#endif

    return fallback;
}

Database::Database()
{
    connection = mysql_init(nullptr);
}

Database::~Database()
{
    if (connection)
    {
        mysql_close(connection);
    }
}

bool Database::connect()
{
    if (!connection)
    {
        std::cerr << "Unable to initialize MySQL connection."
                  << std::endl;
        return false;
    }

    std::string host = getEnv("MYSQL_HOST", "mysql");
    std::string user = getEnv("MYSQL_USER", "tracker");
    std::string password = getEnv("MYSQL_PASSWORD", "tracker_password");
    std::string database = getEnv("MYSQL_DATABASE", "student_task_tracker");

    #ifndef _WIN32
    my_bool verify_server_cert = 0;
    mysql_options(connection, MYSQL_OPT_SSL_VERIFY_SERVER_CERT,
                  &verify_server_cert);
    #endif

    if (!mysql_real_connect(
        connection,
        host.c_str(),
        user.c_str(),
        password.c_str(),
        database.c_str(),
        3306,
        nullptr,
        0
    ))
    {
        std::cerr << "Database connection failed: "
                  << mysql_error(connection) << std::endl;
        return false;
    }

    std::cout << "Connected to MySQL successfully!" << std::endl;
    return true;
}
