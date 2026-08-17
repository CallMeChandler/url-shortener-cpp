cmake_minimum_required(VERSION 3.16)

project(url_shortener)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG master
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(Crow json)

add_executable(url_shortener
    src/main.cpp
    src/storage.cpp
)

target_include_directories(url_shortener PRIVATE include)

target_link_libraries(url_shortener
    Crow::Crow
    nlohmann_json::nlohmann_json
)