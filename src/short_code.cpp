#include "short_code.hpp"

#include <random>

std::string generateShortCode(int length){
    const std::string characters =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(
        0,
        characters.size()-1
    );

    std::string code;

    for (int i = 0; i < length; i++){
        code+=characters[distribution(generator)];
    }

    return code;
}