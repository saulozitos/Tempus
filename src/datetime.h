#pragma once

#include <string>
#include <chrono>
#include "types.h"

using namespace std::chrono;

class DateTime
{
public:

    enum class DateFormat
    {
        YYYYMMDD, //2021-03-23
        DDMMYYYY, //23-03-2021
        YYMMDD,   //21-03-23
        DDMMYY,   //23-03-2021
    };

    explicit DateTime(const DateFormat dateFormat = DateFormat::YYYYMMDD);
    explicit DateTime(const nanoseconds amountTime);
    ~DateTime() = default;

    DateTime(DateTime const&) = delete;
    DateTime& operator =(DateTime const&) = delete;
    DateTime(DateTime&&) = delete;
    DateTime& operator=(DateTime&&) = delete;

    std::string getCurrentDateTimeToString();
    std::string getCurrentTimeToString();
    std::string getCurrentDateToString();

    static bool isLeapYear(const unsigned int year);
    static system_clock::time_point addDays(system_clock::time_point date, const int value);

    Duration::day day() const;
    Duration::hour hour() const;
    Duration::minute minute() const;
    Duration::second second() const;
    Duration::millisecond millisecond() const;

    DateFormat getDateFormat() const;
    void setDateFormat(DateTime::DateFormat dateFormat);

private:
    std::chrono::time_point<system_clock> m_now;
    Duration::millisecond m_ms{};
    std::tm m_bt{};
    DateFormat m_dateFormat{};
    Duration::day m_day{};
    Duration::hour m_hour{};
    Duration::minute m_minute{};
    Duration::second m_second{};
    Duration::millisecond m_millisecond{};
    bool m_isLeapYear;

    void loadValues();
    static int64_t currentMSecsSinceEpoch();
    static std::string getDateFormatToString(DateTime::DateFormat dateFormat);
    void loadDateTimeFromNanoseconds(nanoseconds nsTime);

};

