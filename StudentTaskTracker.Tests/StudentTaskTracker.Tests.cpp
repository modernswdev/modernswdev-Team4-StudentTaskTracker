
#include "pch.h"
#include "CppUnitTest.h"
#include "Task.h"  // Replace with the actual header filename

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentTaskTrackerTests
{
    TEST_CLASS(TaskModelTests)
    {
    public:

        TEST_METHOD(CreateTaskStoresCorrectTitle)
        {
            // Create a task with a known title
            Task task("Operating Systems HW");

            // Check that the title was saved correctly
            Assert::AreEqual(
                std::string("Operating Systems HW"),
                task.getTitle()
            );
        }
    };
}
