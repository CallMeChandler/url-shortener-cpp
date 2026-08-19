#include "time_utils.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string formatTimestamp(
    const std::chrono::system_clock::time_point& timePoint
) {
    std::time_t time =
        std::chrono::system_clock::to_time_t(timePoint);

    std::tm utcTime{};
    gmtime_r(&time, &utcTime);

    std::ostringstream stream;

    stream << std::put_time(
        &utcTime,
        "%Y-%m-%dT%H:%M:%SZ"
    );

    return stream.str();
}

std::string getCurrentTimestamp() {
    return formatTimestamp(
        std::chrono::system_clock::now()
    );
}

std::string getFutureTimestamp(int minutes) {
    auto future =
        std::chrono::system_clock::now()
        + std::chrono::minutes(minutes);

    return formatTimestamp(future);
}

bool isExpired(const std::string& timestamp) {
    if (timestamp.empty()) {
        return false;
    }

    std::tm time{};

    std::istringstream stream(timestamp);

    stream >> std::get_time(
        &time,
        "%Y-%m-%dT%H:%M:%SZ"
    );

    if (stream.fail()) {
        return false;
    }

    std::time_t expiryTime = timegm(&time);

    std::time_t currentTime = std::time(nullptr);

    return currentTime >= expiryTime;
}