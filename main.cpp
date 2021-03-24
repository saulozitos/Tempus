#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

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

    DateTime(const DateFormat dt = DateFormat::YYYYMMDD)
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

    ~DateTime() = default;

    DateTime(DateTime const&) = delete;
    DateTime& operator =(DateTime const&) = delete;
    DateTime(DateTime&&) = delete;
    DateTime& operator=(DateTime&&) = delete;

    inline std::string getCurrentDateTime()
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

    inline std::string getCurrentTime()
    {
        loadValues();
        std::ostringstream oss;
        oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

    inline std::string getCurrentDate()
    {
        loadValues();
        std::array<char, sizeof (bt)>buffer{};
        buffer.fill(0);

        std::strftime(buffer.data(), sizeof(buffer), dateFormat.c_str(), &bt);

        return buffer.data();
    }

private:
    std::chrono::time_point<std::chrono::system_clock> now;
    std::chrono::duration<long, std::ratio<1,1000>> ms{};
    std::tm bt{};
    std::string dateFormat{};

    inline void loadValues()
    {
        // get current time
        now = std::chrono::system_clock::now();
        // get number of milliseconds for the current second (remainder after division into seconds)
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        // convert to std::time_t in order to convert to std::tm (broken time)
        const auto timer = std::chrono::system_clock::to_time_t(now);
        // convert to broken time
        bt = *std::localtime(&timer);
    }
};

int main()
{
    DateTime dt(DateTime::DateFormat::DDMMYYYY);
    std::cout << dt.getCurrentDate() << std::endl;
    std::cout << dt.getCurrentTime() << std::endl;
    std::cout << dt.getCurrentDateTime() << std::endl;
    return 0;
}
