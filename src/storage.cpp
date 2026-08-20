#include "storage.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Storage::Storage(const std::string& filePath) {
    this->filePath = filePath;
}

bool Storage::exists(const std::string& code) {
    std::lock_guard<std::mutex> lock(fileMutex);

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
    std::lock_guard<std::mutex> lock(fileMutex);

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
    std::lock_guard<std::mutex> lock(fileMutex);

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
        std::lock_guard<std::mutex> lock(fileMutex);

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

bool Storage::update(const UrlRecord& record){
    std::lock_guard<std::mutex> lock(fileMutex);

    std::ifstream input(filePath);

    if (!input.is_open()){
        return false;
    }

    json data;
    input >> data;
    input.close();

    bool found = false;

    for (auto& item:data){
        if (item["code"]==record.code){
            item["originalUrl"] = record.originalUrl;
            item["customAlias"] = record.customAlias;
            item["createdAt"] = record.createdAt;
            item["expiresAt"] = record.expiresAt;
            item["lastAccessedAt"] = record.lastAccessedAt;
            item["clicks"] = record.clicks;

            found = true;
            break;
        }
    }

    if (!found){
        return false;
    }

    std::ofstream output(filePath);

    if (!output.is_open()){
        return false;
    }

    output << data.dump(4);

    return true;
}