#include "pch.h"
#include "CppUnitTest.h"
#include "../../include/Task.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentTaskTrackerTests
{
    TEST_CLASS(StudentTaskTrackerTests)
    {
    public:

        TEST_METHOD(SetTaskPriority_ChangesPriority)
        {
            Task task;

            setTaskPriority(task, "High");

            Assert::AreEqual(
                std::string("High"),
                task.priority
            );
        }

        TEST_METHOD(AddTask_ValidTask_AddsTask)
        {
            std::vector<Task> tasks;

            Task task;
            task.title = "Study for Midterm";
            task.course = "Modern Software Development";
            task.dueDate = "10-30-2026";
            task.priority = "High";
            task.status = "Incomplete";
            task.description = "Review unit testing";

            bool result = addTask(tasks, task);

            Assert::IsTrue(result);
            Assert::AreEqual(
                static_cast<size_t>(1),
                tasks.size()
            );
            Assert::AreEqual(
                std::string("Study for Midterm"),
                tasks[0].title
            );
        }

        TEST_METHOD(AddTask_EmptyTitle_DoesNotAddTask)
        {
            std::vector<Task> tasks;

            Task task;
            task.title = "";

            bool result = addTask(tasks, task);

            Assert::IsFalse(result);
            Assert::AreEqual(
                static_cast<size_t>(0),
                tasks.size()
            );
        }
    };
}