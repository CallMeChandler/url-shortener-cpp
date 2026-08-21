#pragma once

#include <string>
#include "models.hpp"
#include <mutex>
#include <vector>

class Storage {
public:
    Storage(const std::string& filePath);

    bool exists(const std::string& code);

    bool findByCode(
        const std::string& code,
        UrlRecord& result
    );

    bool findByOriginalUrl(
        const std::string& url,
        UrlRecord& result
    );

    bool save(const UrlRecord& record);

    bool update(const UrlRecord& record);

    std::vector<UrlRecord> getAll();

private:
    std::string filePath;
    std::mutex fileMutex;
};