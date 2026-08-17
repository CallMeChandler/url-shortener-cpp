#include "storage.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Storage::Storage(const std::string& filePath) {
    this->filePath = filePath;
}

bool Storage::exists(const std::string& code) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    json data;
    file >> data;

    for (const auto& item : data) {
        if (item["code"] == code) {
            return true;
        }
    }

    return false;
}

bool Storage::findByCode(
    const std::string& code,
    UrlRecord& result
) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    json data;
    file >> data;

    for (const auto& item : data) {
        if (item["code"] == code) {
            result.code = item["code"];
            result.originalUrl = item["originalUrl"];
            result.customAlias = item["customAlias"];
            result.createdAt = item["createdAt"];
            result.expiresAt = item["expiresAt"];
            result.lastAccessedAt = item["lastAccessedAt"];
            result.clicks = item["clicks"];

            return true;
        }
    }

    return false;
}

bool Storage::findByOriginalUrl(
    const std::string& url,
    UrlRecord& result
) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    json data;
    file >> data;

    for (const auto& item : data) {
        if (item["originalUrl"] == url) {
            result.code = item["code"];
            result.originalUrl = item["originalUrl"];
            result.customAlias = item["customAlias"];
            result.createdAt = item["createdAt"];
            result.expiresAt = item["expiresAt"];
            result.lastAccessedAt = item["lastAccessedAt"];
            result.clicks = item["clicks"];

            return true;
        }
    }

    return false;
}

bool Storage::save(const UrlRecord& record) {
    json data;

    {
        std::ifstream file(filePath);

        if (file.is_open()) {
            file >> data;
        }
    }

    json newRecord = {
        {"code", record.code},
        {"originalUrl", record.originalUrl},
        {"customAlias", record.customAlias},
        {"createdAt", record.createdAt},
        {"expiresAt", record.expiresAt},
        {"lastAccessedAt", record.lastAccessedAt},
        {"clicks", record.clicks}
    };

    data.push_back(newRecord);

    std::ofstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    file << data.dump(4);

    return true;
}