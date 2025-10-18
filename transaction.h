#pragma once
#include <string>

class Transaction {
public:
    std::string hash() const {
        return "tx_hash";
    }
};
