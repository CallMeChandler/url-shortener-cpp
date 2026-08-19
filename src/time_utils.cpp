#include "time_utils.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentTimestamp(){
    auto now = std::chrono::system_clock::now();

    std::time_t time =
        std::chrono::system_clock::to_time_t(now);

    std::tm utcTime{};

    gmtime_r(&time, &utcTime);

    std::ostringstream stream;

    stream << std::put_time(
        &utcTime,
        "%Y-%m-%dT%H:%M:%SZ"
    );

    return stream.str();
}