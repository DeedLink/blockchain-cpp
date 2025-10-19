#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

class Token {
public:
    std::unordered_map<std::string, uint64_t> balances;

    void mint(const std::string& address, uint64_t amount);
    bool transfer(const std::string& from, const std::string& to, uint64_t amount);
    uint64_t balanceOf(const std::string& address) const;
};
