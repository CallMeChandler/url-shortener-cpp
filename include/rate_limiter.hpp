#pragma once

#include <unordered_map>
#include <deque>
#include <mutex>
#include <string>
#include <chrono>

class RateLimiter{
public:
    bool allowRequest(const std::string& clientIp);

private:
    std::unordered_map<std::string, std::deque<std::chrono::steady_clock::time_point>> requests;

    std::mutex rateMutex;

    const int LIMIT = 5;
    const std::chrono::seconds WINDOW = std::chrono::seconds(60);
};