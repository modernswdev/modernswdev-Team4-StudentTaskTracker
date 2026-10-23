#include "../include/Task.h"

void setTaskPriority(Task& task, const std::string& priority) {
    task.priority = priority;
}

bool addTask(std::vector<Task>& tasks, const Task& task) {
    if (task.title.empty()) {
        return false;
    }

    tasks.push_back(task);
    return true;
}