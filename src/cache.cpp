#include "cache.hpp"

std::optional<UrlRecord> Cache::get(
    const std::string& code
) {
    std::lock_guard<std::mutex> lock(cacheMutex);

    auto it = cache.find(code);

    if (it==cache.end()){
        return std::nullopt;
    }

    return it->second;
}

void Cache::put(const UrlRecord& record) {
    std::lock_guard<std::mutex> lock(cacheMutex);

    cache[record.code] = record;
}

void Cache::remove(const std::string& code){
    std::lock_guard<std::mutex> lock(cacheMutex);

    cache.erase(code);
}