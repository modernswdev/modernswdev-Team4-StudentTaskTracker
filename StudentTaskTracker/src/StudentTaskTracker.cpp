#include <iostream>
#include "../include/Database.h"

int main()
{
    std::cout << "Student Task and Assignment Tracker" << std::endl;

    Database db;
    db.connect();

    return 0;
}