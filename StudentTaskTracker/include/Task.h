#pragma once
#include <string>

struct Task {
    std::string title;
    std::string course;
    std::string dueDate;
    std::string priority;
    std::string status;
    std::string description;
};

void setTaskPriority(Task& task, const std::string& priority);
