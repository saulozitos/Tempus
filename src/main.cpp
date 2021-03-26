#include <iostream>
#include "datetime.h"
#include "chronometer.h"

int main()
{
    Chronometer c;
    DateTime dt;

    std::cout << "Current date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Current time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Current date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    constexpr auto t = 9.127;
    while (c.elapsedSeconds() < t){}

    std::cout << "Current date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Current time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Current date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    std::cout << "\nRestart chronometer\n" << std::endl;
    c.reset();
    std::cout << "Current date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Current time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Current date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    constexpr auto tt = 5.345;
    while (c.elapsedSeconds() < tt){}

    std::cout << "Current date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Current time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Current date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    return 0;
}
