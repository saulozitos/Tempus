#pragma once

#include <string>
#include <chrono>

using namespace std::chrono;

namespace Ratio {
using hours = std::ratio<3600, 1>;
using minutes = std::ratio<60, 1>;
using seconds = std::ratio<1, 1>;
using milliseconds = std::ratio<1, 1000>;
using days = std::ratio<86400>;
using weeks = std::ratio<604800>;
using months = std::ratio<2629746>;
using years = std::ratio<31556952>;
}

namespace Duration {
using day = duration<int64_t, Ratio::days>;
using hour = duration<int64_t, Ratio::hours>;
using minute = duration<int64_t, Ratio::minutes>;
using second = duration<int64_t, Ratio::seconds>;
using millisecond = duration<int64_t, Ratio::milliseconds>;
}

using days = duration<int64_t, Ratio::days>;
using weeks = duration<int64_t, Ratio::weeks>;
using months = duration<int64_t, Ratio::months>;
using years = duration<int64_t, Ratio::years>;


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

    void loadValues();
    static int64_t currentMSecsSinceEpoch();
    static std::string getDateFormatToString(DateTime::DateFormat dateFormat);
    void loadDateTimeFromNanoseconds(nanoseconds nsTime);

};

