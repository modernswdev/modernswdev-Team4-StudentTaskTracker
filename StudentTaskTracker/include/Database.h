#pragma once
#include <mysql.h>
#include <string>
#include <vector>
#include "Task.h"
class Database {
public:
    Database();
    ~Database();

    bool connect();

    bool addTaskToDatabase(
        const std::string& title,
        const std::string& course,
        const std::string& dueDate,
        const std::string& priority,
        const std::string& status,
        const std::string& description
    );
    bool validateUser(
        const std::string& username,
        const std::string& password
    );
    void getAllTasks();

    std::vector<Task> getTasks();

    bool updateTaskStatus(
        int id,
        const std::string& status
    );

private:
    MYSQL* connection;
};