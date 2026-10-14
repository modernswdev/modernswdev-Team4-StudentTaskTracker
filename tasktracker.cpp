#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

// Structure for Student Task and Assignment Tracker, which should include:
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

    std::cout << "Enter Due Date (MM-DD-YYYY or Oct 12): ";
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
    for (size_t i=0; i < tasks.size(); ++i) {
        std::cout << "Task #" << (i + 1) << "\n";
        std::cout << "Title: "<< tasks[i].title << "\n";
        std::cout << "Course: "<< tasks[i].course << "\n";
        std::cout << "Due Date: "<< tasks[i].dueDate << "\n";
        std::cout << "Priority: "<< tasks[i].priority << "\n";
        std::cout << "Status: "<< tasks[i].status << "\n";
        std::cout << "Description: "<< tasks[i].description << "\n";
        std::cout << "=============================================================\n";
    }
}

int main() {
    std:: vector<Task> taskList;
    int choice = 0;

    do {
        std::cout << "\n========================================\n";
        std::cout << "====STUDENT TASK & ASSIGNMENT TRACKER===\n";
        std::cout << "========================================\n";
        std::cout << "1. Add a New Task\n";
        std::cout << "2. View All Tasks\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter an option (1-3): ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            clearInput();
            continue;
        }

        clearInput();

        switch (choice) {
        case 1:
            taskList.push_back(newTask());
            break;
        case 2:
            displayTasks(taskList);
            break;
        case 3:
            std::cout << "\nExiting task tracker. Goodbye!\n";
            break;     
        default:
            std::cout << "\n Invalid choice. Please enter 1, 2, or 3.\n";
            break;
        }
    } while (choice != 3);

    return 0;
    {
    }
    
}
