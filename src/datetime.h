#pragma once

#include <string>
#include <chrono>

class Date
{
public:
private:
};

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
    explicit DateTime(const std::chrono::nanoseconds amountTime);
    ~DateTime() = default;

    DateTime(DateTime const&) = delete;
    DateTime& operator =(DateTime const&) = delete;
    DateTime(DateTime&&) = delete;
    DateTime& operator=(DateTime&&) = delete;

    std::string getCurrentDateTimeToString();
    std::string getCurrentTimeToString();
    std::string getCurrentDateToString();

    static bool isLeapYear(const unsigned int year);
    static std::chrono::system_clock::time_point addDays(std::chrono::system_clock::time_point date, const int value);

    std::chrono::duration<int, std::ratio<86400, 1> > day() const;
    std::chrono::duration<long, std::ratio<3600, 1> > hour() const;
    std::chrono::duration<long, std::ratio<60, 1> > minute() const;
    std::chrono::duration<long, std::ratio<1, 1> > second() const;
    std::chrono::duration<long, std::ratio<1, 1000> > mSecond() const;

private:
    std::chrono::time_point<std::chrono::system_clock> m_now;
    std::chrono::duration<long, std::ratio<1,1000>> m_ms{};
    std::tm m_bt{};
    std::string m_dateFormat{};
    std::chrono::duration<int, std::ratio<86400, 1>>m_day{};
    std::chrono::duration<long, std::ratio<3600, 1>>m_hour{};
    std::chrono::duration<long, std::ratio<60, 1>>m_minute{};
    std::chrono::duration<long, std::ratio<1, 1>>m_second{};
    std::chrono::duration<long, std::ratio<1, 1000>>m_mSecond{};

    void loadValues();
    static int64_t currentMSecsSinceEpoch();
    static std::string getDateFormat(const DateFormat dateFormat);
    void loadDateTimeFromNanoseconds(std::chrono::nanoseconds nsTime);

};

