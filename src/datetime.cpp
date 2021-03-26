#include "datetime.h"

#include <array>
#include <sstream>
#include <iomanip>

DateTime::DateTime(const DateTime::DateFormat dt)
{
    switch (dt) {
    case DateFormat::YYYYMMDD:
        dateFormat = "%Y-%m-%d";
        break;
    case DateFormat::DDMMYYYY:
        dateFormat = "%d-%m-%Y";
        break;
    case DateFormat::YYMMDD:
        dateFormat = "%y-%m-%d";
        break;
    case DateFormat::DDMMYY:
        dateFormat = "%d-%m-%y";
        break;
    default:
        break;
    }
}

std::string DateTime::getCurrentDateTimeToString()
{
    loadValues();

    std::array<char, sizeof (bt)>buffer{};
    buffer.fill(0);

    std::strftime(buffer.data(), sizeof(buffer), "%Y-%m-%d ", &bt);

    std::ostringstream oss;
    oss << buffer.data();
    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string DateTime::getCurrentTimeToString()
{
    loadValues();
    std::ostringstream oss;
    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

std::string DateTime::getCurrentDateToString()
{
    loadValues();
    std::array<char, sizeof (bt)>buffer{};
    buffer.fill(0);

    std::strftime(buffer.data(), sizeof(buffer), dateFormat.c_str(), &bt);

    return buffer.data();
}

bool DateTime::isLeapYear(const unsigned int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

std::chrono::system_clock::time_point DateTime::addDays(std::chrono::system_clock::time_point date, const int value)
{
    return date + std::chrono::hours(value * 24);
}

void DateTime::loadValues()
{
    // get current time
    now = std::chrono::system_clock::now();
    // get number of milliseconds for the current second (remainder after division into seconds)
    constexpr auto msToSec{1000};
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % msToSec;
    // convert to std::time_t in order to convert to std::tm (broken time)
    const auto timer = std::chrono::system_clock::to_time_t(now);
    // convert to broken time
    bt = *std::localtime(&timer);
}
