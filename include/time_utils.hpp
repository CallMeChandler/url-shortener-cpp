#pragma once

#include <string>

std::string getCurrentTimestamp();
std::string getFutureTimestamp(int minutes);
bool isExpired(const std::string& timestamp);