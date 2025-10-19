#pragma once
#include <string>
#include <cstdint>

class Transaction {
public:
    std::string type;
    std::string from;
    std::string to;
    uint64_t amount;

    Transaction(const std::string& t, const std::string& f, const std::string& tt, uint64_t a);

    std::string hash() const;
};
