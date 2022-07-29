#include "datetime.h"

#include <array>
#include <sstream>
#include <iomanip>

namespace Constants
{
constexpr auto msToSec{1000};
}

DateTime::DateTime(const DateTime::DateFormat dateFormat) : m_dateFormat(dateFormat)
    , m_isLeapYear(false)
{}

DateTime::DateTime(const nanoseconds amountTime) : m_isLeapYear(false)
{
    loadDateTimeFromNanoseconds(amountTime);
}

std::string DateTime::getCurrentDateTimeToString()
{
    loadValues();

    std::array<char, sizeof (m_bt)>buffer{};
    buffer.fill(0);

    std::strftime(buffer.data(), sizeof(buffer), "%Y-%m-%d ", &m_bt);

    std::stringstream ss;
    ss << buffer.data();
    ss << std::put_time(&m_bt, "%H:%M:%S"); // HH:MM:SS
    ss << '.' << std::setfill('0') << std::setw(3) << m_ms.count();

    return ss.str();
}
#include <iostream>
std::string DateTime::getCurrentTimeToString()
{
    loadValues();
    std::stringstream ss;
    ss << std::put_time(&m_bt, "%H:%M:%S"); // HH:MM:SS
    ss << '.' << std::setfill('0') << std::setw(3) << m_ms.count();

    auto hora = m_bt.tm_hour;
    auto min = m_bt.tm_min;
    auto sec = m_bt.tm_sec;
    auto dia = m_bt.tm_mday;
    auto mes = m_bt.tm_mon;
    auto ano = m_bt.tm_year;
    std::cout << "teste: " << hora << ":" << min << ":" << sec << " - "
              << dia << "/" << mes+1 << "/" << ano+1900 << '\n';

    return ss.str();
}

std::string DateTime::getCurrentDateToString()
{
    loadValues();
    std::array<char, sizeof (m_bt)>buffer{};
    buffer.fill(0);

    std::strftime(buffer.data(), sizeof(buffer), getDateFormatToString(m_dateFormat).c_str(), &m_bt);

    return buffer.data();
}

bool DateTime::isLeapYear(const unsigned int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

system_clock::time_point DateTime::addDays(system_clock::time_point date, const int value)
{
    return date + hours(value * 24);
}

Duration::day DateTime::day() const
{
    return m_day;
}

Duration::hour DateTime::hour() const
{
    return m_hour;
}

Duration::minute DateTime::minute() const
{
    return m_minute;
}

Duration::second DateTime::second() const
{
    return m_second;
}

Duration::millisecond DateTime::millisecond() const
{
    return m_millisecond;
}

DateTime::DateFormat DateTime::getDateFormat() const
{
    return m_dateFormat;
}

void DateTime::setDateFormat(DateTime::DateFormat dateFormat)
{
    m_dateFormat = dateFormat;
}

void DateTime::loadValues()
{
    // get current time
    m_now = system_clock::now();

    // get number of milliseconds for the current second (remainder after division into seconds)
    m_ms = duration_cast<milliseconds>(m_now.time_since_epoch()) % Constants::msToSec;

    // convert to std::time_t in order to convert to std::tm (broken time)
    const auto timer = system_clock::to_time_t(m_now);

    // convert to broken time
    m_bt = *std::localtime(&timer);
}

int64_t DateTime::currentMSecsSinceEpoch()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::string DateTime::getDateFormatToString(DateTime::DateFormat dateFormat)
{
    switch (dateFormat) {
    case DateFormat::YYYYMMDD:
        return std::string("%Y-%m-%d");
    case DateFormat::DDMMYYYY:
        return std::string("%d-%m-%Y");
    case DateFormat::YYMMDD:
        return std::string("%y-%m-%d");
    case DateFormat::DDMMYY:
        return std::string("%d-%m-%y");
    }
    return {};
}

void DateTime::loadDateTimeFromNanoseconds(nanoseconds nsTime)
{
    m_day = duration_cast<days>(nsTime);
    nsTime -= m_day;
    m_hour = duration_cast<hours>(nsTime);
    nsTime -= m_hour;
    m_minute = duration_cast<minutes>(nsTime);
    nsTime -= m_minute;
    m_second = duration_cast<seconds>(nsTime);
    nsTime -= m_second;
    m_millisecond = duration_cast<milliseconds>(nsTime);
}

