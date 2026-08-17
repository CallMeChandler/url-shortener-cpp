#pragma once
#include <string>

struct UrlRecord {
    std::string code;
    std::string originalUrl;
    bool customAlias;

    std::string createdAt;
    std::string expiresAt;
    std::string lastAccessedAt;

    long long clicks;
};