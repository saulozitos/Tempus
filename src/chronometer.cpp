#include "chronometer.h"

#include <sstream>
#include <iomanip>
#include "datetime.h"

using namespace std::chrono;

namespace Constants
{
    //constexpr auto oneDayInSeconds{86400};
    constexpr auto msToSec{1000.00};
}


Chronometer::Chronometer()
{
    start();
}

std::string Chronometer::formateTime(std::chrono::nanoseconds totalTime)
{
    const auto dt = DateTime(totalTime);

    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << dt.day().count() << "d:"
       << std::setfill('0') << std::setw(2) << dt.hour().count() << ":"
       << std::setfill('0') << std::setw(2) << dt.minute().count() << ":"
       << std::setfill('0') << std::setw(2) << dt.second().count() << "."
       << std::setfill('0') << std::setw(3) << dt.mSecond().count();

    return os.str();
}

std::chrono::time_point<std::chrono::steady_clock> Chronometer::getTimePointNow()
{
    return m_isRunning ? steady_clock::now() : m_EndTime;
}

void Chronometer::start()
{
    if(!m_isRunning)
    {
        m_StartTime = steady_clock::now();
        m_isRunning = true;
    }
}

void Chronometer::stop()
{
    if(m_isRunning)
    {
        m_EndTime = steady_clock::now();
        m_isRunning = false;
    }
}

void Chronometer::reset()
{
    if(m_isRunning)
    {
        stop();
        start();
    }
}

double Chronometer::elapsedMilliseconds()
{
    return duration_cast<milliseconds>(getTimePointNow() - m_StartTime).count();
}

double Chronometer::elapsedSeconds()
{
    return elapsedMilliseconds() / Constants::msToSec;
}

std::string Chronometer::elapsedTimeToString()
{
    return formateTime(duration_cast<nanoseconds>(getTimePointNow() - m_StartTime));
}
