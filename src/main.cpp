#include "crow.h"
#include "storage.hpp"
#include "models.hpp"
#include "short_code.hpp"
#include "validation.hpp"

#include <iostream>
#include <string>

int main() {
    crow::SimpleApp app;

    Storage storage("../data/urls.json");

    // std::cout << generateShortCode() << "\n";
    // std::cout << isValidUrl("https://google.com") << "\n";
    // std::cout << isValidUrl("hello") << "\n";

    CROW_ROUTE(app, "/")([](){
        return "URL Shortener is running!";
    });

    CROW_ROUTE(app, "/api/shorten")
    .methods(crow::HTTPMethod::POST)
    ([&storage](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(
                400,
                R"({"error":"Invalid JSON"})"
            );
        }

        if (!body.has("url")){
            return crow::response(
                400,
                R"({"error":"URL is required"})"
            );
        }

        std::string originalUrl = body["url"].s();

        if (!isValidUrl(originalUrl)){
            return crow::response(
                400,
                R"({"error":"Invalid URL"})"
            );
        }

        UrlRecord existing;

        if (storage.findByOriginalUrl(originalUrl, existing)){
            crow::json::wvalue response;

            response["code"] = existing.code;
            response["shortUrl"] = "https://localhost:8080/"+existing.code;

            response["existing"] = true;

            return crow::response(200, response);
        }

        std::string code;
        bool customAlias = false;

        if (body.has("alias") && body["alias"].t()==crow::json::type::String){
            std::string alias = body["alias"].s();

            if (!alias.empty()) {
                if (storage.exists(alias)){
                    return crow::response(
                        409,
                        R"({"error":"Alias already exists"})"
                    );
                }
                code = alias;
                customAlias = true;
            }
        }

        if (!customAlias){
            do {
                code = generateShortCode();
            } while (storage.exists(code));
        }

        UrlRecord record;

        record.code = code;
        record.originalUrl = originalUrl;
        record.customAlias = customAlias;

        record.createdAt = "";
        record.expiresAt = "";
        record.lastAccessedAt = "";

        record.clicks = 0;

        if (!storage.save(record)){
            return crow::response(
                500,
                R"({"error":"Failed to save the URL"})"
            );
        }

        crow::json::wvalue response;

        response["code"] = code;
        response["shortUrl"] = "http://localhost:8080/" + code;

        response["originalUrl"] = originalUrl;
        response["existing"] = false;

        return crow::response(201, response);

    });

    CROW_ROUTE(app, "/<string>")
    ([&storage](const std::string& code){
        UrlRecord record;

        if (!storage.findByCode(code, record)){
            return crow::response(
                404,
                "Short URL not found"
            );
        }

        crow::response response(302);

        response.add_header(
            "Location",
            record.originalUrl
        );

        return response;
    });

    app.port(8080).multithreaded().run();
}