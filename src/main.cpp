#include "crow.h"
#include "storage.hpp"
#include "models.hpp"

#include <iostream>

int main() {
    crow::SimpleApp app;

    Storage storage("../data/urls.json");

    UrlRecord testRecord;
    testRecord.code = "abc123";
    testRecord.originalUrl = "https://example.com";
    testRecord.customAlias = false;
    testRecord.createdAt = "2026-08-18T04:00:00";
    testRecord.expiresAt = "";
    testRecord.lastAccessedAt = "";
    testRecord.clicks = 0;

    if (!storage.exists(testRecord.code)) {
        if (storage.save(testRecord)) {
            std::cout << "Test record saved successfully\n";
        } else {
            std::cout << "Failed to save test record\n";
        }
    } else {
        std::cout << "Test record already exists\n";
    }

    CROW_ROUTE(app, "/")([](){
        return "URL Shortener is running!";
    });

    app.port(8080).multithreaded().run();
}