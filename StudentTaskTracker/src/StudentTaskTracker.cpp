#include <iostream>

#include "../include/third_party/httplib.h"
#include "../include/third_party/json.hpp"

#include "../include/Database.h"

using json = nlohmann::json;

int main()
{
    std::cout << "Student Task and Assignment Tracker API" << std::endl;

    Database db;

    if (!db.connect()) {
        return 1;
    }

    httplib::Server server;

    server.set_mount_point("/", "../frontend");

    server.set_default_headers({
    { "Access-Control-Allow-Origin", "*" },
    { "Access-Control-Allow-Headers", "Content-Type" },
    { "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS" }
        });

    server.Options(R"(.*)", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
        });

    server.Get("/api/test", [](const httplib::Request&, httplib::Response& res) {
        json response;
        response["message"] = "Backend is working";

        res.set_content(response.dump(), "application/json");
        });
    server.Post("/api/login", [&db](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);

            std::string username = body.value("username", "");
            std::string password = body.value("password", "");

            if (username.empty() || password.empty()) {
                res.status = 400;
                res.set_content(
                    R"({"error":"Username and password are required"})",
                    "application/json"
                );
                return;
            }

            bool valid = db.validateUser(username, password);

            if (!valid) {
                res.status = 401;
                res.set_content(
                    R"({"error":"Invalid username or password"})",
                    "application/json"
                );
                return;
            }

            res.set_content(
                R"({"message":"Login successful"})",
                "application/json"
            );
        }
        catch (...) {
            res.status = 400;
            res.set_content(
                R"({"error":"Invalid request"})",
                "application/json"
            );
        }
        });

    server.Get("/api/assignments", [&db](const httplib::Request&, httplib::Response& res) {
        std::vector<Task> tasks = db.getTasks();

        json response = json::array();

        for (const auto& task : tasks) {
            response.push_back({
                {"id", task.id},
                {"title", task.title},
                {"course", task.course},
                {"dueDate", task.dueDate},
                {"priority", task.priority},
                {"status", task.status},
                {"description", task.description}
                });
        }

        res.set_content(response.dump(), "application/json");
        });
    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_redirect("/login.html");
        });
    server.Post("/api/assignments", [&db](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);

            std::string title = body.value("title", "");
            std::string course = body.value("course", "");
            std::string dueDate = body.value("dueDate", "");
            std::string priority = body.value("priority", "");
            std::string status = body.value("status", "To Do");
            std::string description = body.value("description", "");

            if (title.empty()) {
                res.status = 400;
                res.set_content(
                    R"({"error":"Title is required"})",
                    "application/json"
                );
                return;
            }

            bool added = db.addTaskToDatabase(
                title,
                course,
                dueDate,
                priority,
                status,
                description
            );

            if (!added) {
                res.status = 500;
                res.set_content(
                    R"({"error":"Failed to save assignment"})",
                    "application/json"
                );
                return;
            }

            res.status = 201;
            res.set_content(
                R"({"message":"Assignment saved successfully"})",
                "application/json"
            );
        }
        catch (...) {
            res.status = 400;
            res.set_content(
                R"({"error":"Invalid JSON"})",
                "application/json"
            );
        }
        });
    server.Put(R"(/api/assignments/(\d+))",
        [&db](const httplib::Request& req, httplib::Response& res) {
            try {
                int id = std::stoi(req.matches[1].str());

                json body = json::parse(req.body);
                std::string status = body.value("status", "");

                if (status.empty()) {
                    res.status = 400;
                    res.set_content(
                        R"({"error":"Status is required"})",
                        "application/json"
                    );
                    return;
                }

                bool updated = db.updateTaskStatus(id, status);

                if (!updated) {
                    res.status = 500;
                    res.set_content(
                        R"({"error":"Failed to update task"})",
                        "application/json"
                    );
                    return;
                }

                res.set_content(
                    R"({"message":"Task updated successfully"})",
                    "application/json"
                );
            }
            catch (...) {
                res.status = 400;
                res.set_content(
                    R"({"error":"Invalid request"})",
                    "application/json"
                );
            }
        }
    );

    int port = server.bind_to_port("127.0.0.1", 8080);

    if (port == -1) {
        std::cout << "ERROR: Could not bind to port 8080." << std::endl;
        return 1;
    }

    std::cout << "Server successfully bound to port 8080" << std::endl;
    std::cout << "Open: http://127.0.0.1:8080/api/test" << std::endl;

    server.listen_after_bind();

    return 0;
}