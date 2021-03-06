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
    void reset();
    double elapsedMilliseconds();
    double elapsedSeconds();
    std::string elapsedTimeToString();

private:
    std::chrono::time_point<std::chrono::steady_clock> m_StartTime{};
    std::chrono::time_point<std::chrono::steady_clock> m_EndTime{};
    bool m_isRunning = false;
    static std::string formateTime(std::chrono::nanoseconds totalTime);
    std::chrono::time_point<std::chrono::steady_clock> getTimePointNow();
};


