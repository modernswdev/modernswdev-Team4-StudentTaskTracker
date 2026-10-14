#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

// Basic task structure for Student Task and Assignment Tracker, which should include:
// Task Title
// Course
// Due Date
// Priority
// Status
// Description

struct Task {
    std:: string title;
    std:: string course;
    std:: string dueDate;
    std:: string priority;
    std:: string status;
    std:: string description;
};

// Function to clear newline characters from input
void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function used to enter a new task or assignment
Task newTask() {
    Task task;

    std::cout << "\n==================================\n";
    std::cout << "===========ENTER NEW TASK==========\n";
    std::cout << "===================================\n";

    std::cout << "Enter Task Title: ";
    std::getline(std::cin, task.title);

    std::cout << "Enter Course: ";
    std::getline(std::cin, task.course);

    std::cout << "Enter Due Date: ";
    std::getline(std::cin, task.dueDate);

    std::cout << "Enter Priority (High, Medium, Low): ";
    std::getline(std::cin, task.priority);

    std::cout << "Enter Status (Incomplete, Complete, Overdue): ";
    std::getline(std::cin, task.status);

    std::cout << "Enter Description: ";
    std::getline(std::cin, task.description);

    std::cout << "\n Task Entered Successfully!\n";
    return task;
}   

// Function that will print a list of all tasks entered
void displayTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "\n No tasks entered.\n";
        return;
    }

    std::cout <<"========================CURRENT TASK LIST=====================\n";
    for (size_t i=0; i < tasks.size(); ==i) {
        std::cout << "Task #" << (i + 1) << "\n";
        std::cout << "Title: "<< tasks[i].title << "\n";
        std::cout << "Course: "<< tasks[i].course << "\n";
        std::cout << "Due Date: "<< tasks[i].dueDate << "\n";
        std::cout << "Priority: "<< tasks[i].priority << "\n";
        std::cout << "Status: "<< tasks[i].status << "\n";
        std::cout << "Description: "<< tasks[i].description << "\n";
        std::cout << "=========================================================\n";
    }
}
