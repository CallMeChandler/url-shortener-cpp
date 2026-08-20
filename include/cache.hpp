#pragma once

#include <unordered_map>
#include <string>
#include <optional>
#include <mutex>

#include <models.hpp>

class Cache{
public:
    std::optional<UrlRecord> get(const std::string& code);

    void put(const UrlRecord& record);

    void remove(const std::string& code);

private:
    std::unordered_map<std::string, UrlRecord> cache;
    std::mutex cacheMutex;
};