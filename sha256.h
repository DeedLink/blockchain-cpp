#pragma once
#include <string>
#include <sstream>

inline std::string sha256(const std::string& str) {
    std::stringstream ss;
    for (char c : str) ss << std::hex << (int)c;
    return ss.str();
}
