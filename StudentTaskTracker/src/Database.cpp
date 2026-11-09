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

    char* dbPassword = nullptr;
    size_t passwordLength = 0;

    if (_dupenv_s(
        &dbPassword,
        &passwordLength,
        "STUDENT_TRACKER_DB_PASSWORD"
    ) != 0 || dbPassword == nullptr) {

        std::cout
            << "Database password environment variable is not set."
            << std::endl;

        return false;
    }

    connection = mysql_real_connect(
        connection,
        "localhost",
        "root",
        dbPassword,
        "student_task_tracker",
        3306,
        nullptr,
        0
    );

    free(dbPassword);

    if (!connection) {
        std::cout
            << "Database connection failed."
            << std::endl;

        return false;
    }

    std::cout
        << "Connected to MySQL successfully!"
        << std::endl;

    return true;
}

bool Database::addTaskToDatabase(
    const std::string& title,
    const std::string& course,
    const std::string& dueDate,
    const std::string& priority,
    const std::string& status,
    const std::string& description
) {
    if (!connection) {
        std::cout
            << "Database connection failed."
            << std::endl;

        return false;
    }

    auto escape = [this](const std::string& value) {
        std::string escaped(
            value.size() * 2 + 1,
            '\0'
        );

        unsigned long length =
            mysql_real_escape_string(
                connection,
                &escaped[0],
                value.c_str(),
                static_cast<unsigned long>(
                    value.size()
                    )
            );

        escaped.resize(length);
        return escaped;
        };

    std::string query =
        "INSERT INTO tasks "
        "(title, course, dueDate, priority, status, description) "
        "VALUES ('" +
        escape(title) + "', '" +
        escape(course) + "', '" +
        escape(dueDate) + "', '" +
        escape(priority) + "', '" +
        escape(status) + "', '" +
        escape(description) + "')";

    if (mysql_query(
        connection,
        query.c_str()
    ) != 0) {

        std::cout
            << "Failed to add task: "
            << mysql_error(connection)
            << std::endl;

        return false;
    }

    std::cout
        << "Task added to database successfully!"
        << std::endl;

    return true;
}

void Database::getAllTasks()
{
    if (!connection) {
        std::cout
            << "No database connection."
            << std::endl;

        return;
    }

    const char* query =
        "SELECT * FROM tasks";

    if (mysql_query(
        connection,
        query
    ) != 0) {

        std::cout
            << "Failed to retrieve tasks: "
            << mysql_error(connection)
            << std::endl;

        return;
    }

    MYSQL_RES* result =
        mysql_store_result(connection);

    if (!result) {
        std::cout
            << "No tasks found."
            << std::endl;

        return;
    }

    MYSQL_ROW row;

    std::cout
        << "\nTasks in database:"
        << std::endl;

    while (
        (row = mysql_fetch_row(result))
        ) {
        std::cout
            << "ID: "
            << (row[0] ? row[0] : "")
            << " | Title: "
            << (row[1] ? row[1] : "")
            << " | Course: "
            << (row[2] ? row[2] : "")
            << " | Due Date: "
            << (row[3] ? row[3] : "")
            << " | Priority: "
            << (row[4] ? row[4] : "")
            << " | Status: "
            << (row[5] ? row[5] : "")
            << " | Description: "
            << (row[6] ? row[6] : "")
            << std::endl;
    }

    mysql_free_result(result);
}

std::vector<Task> Database::getTasks()
{
    std::vector<Task> tasks;

    if (!connection) {
        return tasks;
    }

    const char* query =
        "SELECT id, title, course, dueDate, "
        "priority, status, description "
        "FROM tasks";

    if (mysql_query(
        connection,
        query
    ) != 0) {

        std::cout
            << "Failed to retrieve tasks: "
            << mysql_error(connection)
            << std::endl;

        return tasks;
    }

    MYSQL_RES* result =
        mysql_store_result(connection);

    if (!result) {
        return tasks;
    }

    MYSQL_ROW row;

    while (
        (row = mysql_fetch_row(result))
        ) {
        Task task;

        task.id =
            row[0]
            ? std::stoi(row[0])
            : 0;

        task.title =
            row[1]
            ? row[1]
            : "";

        task.course =
            row[2]
            ? row[2]
            : "";

        task.dueDate =
            row[3]
            ? row[3]
            : "";

        task.priority =
            row[4]
            ? row[4]
            : "";

        task.status =
            row[5]
            ? row[5]
            : "";

        task.description =
            row[6]
            ? row[6]
            : "";

        tasks.push_back(task);
    }

    mysql_free_result(result);

    return tasks;
}

bool Database::updateTaskStatus(
    int id,
    const std::string& status
) {
    if (!connection) {
        std::cout
            << "No database connection."
            << std::endl;

        return false;
    }

    std::string escapedStatus(
        status.size() * 2 + 1,
        '\0'
    );

    unsigned long length =
        mysql_real_escape_string(
            connection,
            &escapedStatus[0],
            status.c_str(),
            static_cast<unsigned long>(
                status.size()
                )
        );

    escapedStatus.resize(length);

    std::string query =
        "UPDATE tasks SET status = '" +
        escapedStatus +
        "' WHERE id = " +
        std::to_string(id);

    if (mysql_query(
        connection,
        query.c_str()
    ) != 0) {

        std::cout
            << "Failed to update task status: "
            << mysql_error(connection)
            << std::endl;

        return false;
    }

    std::cout
        << "Task status updated successfully!"
        << std::endl;

    return true;
}

bool Database::validateUser(
    const std::string& username,
    const std::string& password
) {
    if (!connection) {
        std::cout
            << "No database connection."
            << std::endl;

        return false;
    }

    std::string escapedUsername(
        username.size() * 2 + 1,
        '\0'
    );

    unsigned long usernameLength =
        mysql_real_escape_string(
            connection,
            &escapedUsername[0],
            username.c_str(),
            static_cast<unsigned long>(
                username.size()
                )
        );

    escapedUsername.resize(
        usernameLength
    );

    std::string escapedPassword(
        password.size() * 2 + 1,
        '\0'
    );

    unsigned long passwordLength =
        mysql_real_escape_string(
            connection,
            &escapedPassword[0],
            password.c_str(),
            static_cast<unsigned long>(
                password.size()
                )
        );

    escapedPassword.resize(
        passwordLength
    );

    std::string query =
        "SELECT id FROM users "
        "WHERE username='" +
        escapedUsername +
        "' AND password='" +
        escapedPassword +
        "' LIMIT 1";

  

    if (mysql_query(
        connection,
        query.c_str()
    ) != 0) {

        std::cout
            << "Login query failed: "
            << mysql_error(connection)
            << std::endl;

        return false;
    }

    MYSQL_RES* result =
        mysql_store_result(connection);

    if (!result) {
        std::cout
            << "No login result returned."
            << std::endl;

        return false;
    }

    bool valid =
        mysql_num_rows(result) > 0;

    mysql_free_result(result);

    return valid;
}