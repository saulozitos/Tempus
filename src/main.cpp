#include <iostream>
#include "datetime.h"
#include "chronometer.h"

int main()
{
    Chronometer c;
    DateTime dt(DateTime::DateFormat::DDMMYY);

    std::cout << dt.getCurrentDateTime() << std::endl;
    std::cout << "NOW: " << c.elapsedTimeToString() << std::endl;
    constexpr auto t = 10.12;
    while (c.elapsedSeconds() < t) {
    }

    std::cout << dt.getCurrentDateTime() << std::endl;
    std::cout << "NOW: " << c.elapsedTimeToString() << std::endl;
    return 0;
}
