#include <iostream>
#include "../include/Database.h"

int main()
{
    std::cout << "Student Task and Assignment Tracker" << std::endl;

    Database db;

    if (!db.connect()) {
        std::cerr << "Unable to start application: database connection failed."
                  << std::endl;
        return 1;
    }

    return 0;
}
