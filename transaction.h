#pragma once
#include <string>
#include "sha256.h"

class Transaction {
public:
    std::string data;
    Transaction(const std::string& d) : data(d) {}
    std::string hash() const;
};
