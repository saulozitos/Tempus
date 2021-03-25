#pragma once

#include <string>
#include <chrono>

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

    DateTime(const DateFormat dt = DateFormat::YYYYMMDD);

    ~DateTime() = default;

    DateTime(DateTime const&) = delete;
    DateTime& operator =(DateTime const&) = delete;
    DateTime(DateTime&&) = delete;
    DateTime& operator=(DateTime&&) = delete;

    std::string getCurrentDateTime();
    std::string getCurrentTime();
    std::string getCurrentDate();

private:
    std::chrono::time_point<std::chrono::system_clock> now;
    std::chrono::duration<long, std::ratio<1,1000>> ms{};
    std::tm bt{};
    std::string dateFormat{};
    void loadValues();
};

