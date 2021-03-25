#include <iostream>
#include "datetime.h"
#include "chronometer.h"

int main()
{
    Chronometer c;
    DateTime dt;

    std::cout << "Currente date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Currente time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Currente date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    constexpr auto t = 9.127;
    while (c.elapsedSeconds() < t){}

    std::cout << "Currente date: " << dt.getCurrentDateToString() << std::endl;
    std::cout << "Currente time: " << dt.getCurrentTimeToString() << std::endl;
    std::cout << "Currente date time: " << dt.getCurrentDateTimeToString() << std::endl;
    std::cout << "Chronometer now: " << c.elapsedTimeToString() << std::endl;

    return 0;
}
