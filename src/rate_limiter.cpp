#include "rate_limiter.hpp"

bool RateLimiter::allowRequest(
    const std::string& clientIp
) {
    std::lock_guard<std::mutex> lock(rateMutex);

    auto now = std::chrono::steady_clock::now();

    auto& userRequests = requests[clientIp];

    while (!userRequests.empty() && now-userRequests.front()>WINDOW){
        userRequests.pop_front();
    }

    if (userRequests.size()>=LIMIT){
        return false;
    }

    userRequests.push_back(now);

    return true;
}