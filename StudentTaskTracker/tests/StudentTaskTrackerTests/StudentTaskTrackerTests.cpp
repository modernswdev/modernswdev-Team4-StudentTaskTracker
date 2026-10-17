#include "pch.h"
#include "CppUnitTest.h"
#include "../../include/Task.h"

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
    };
}