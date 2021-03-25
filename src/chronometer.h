#pragma once

#include <chrono>
#include <string>

class Chronometer
{
public:
    Chronometer();
    ~Chronometer() = default;

    void start();
    void stop();
    double elapsedMilliseconds();
    double elapsedSeconds();
    std::string elapsedTimeToString();

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime{};
    std::chrono::time_point<std::chrono::system_clock> m_EndTime{};
    bool m_isRunning = false;
    static std::string formateTime(std::chrono::nanoseconds ns);
    std::chrono::time_point<std::chrono::system_clock> getTimePointNow();
};

