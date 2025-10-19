#include "transaction.h"
#include "sha256.h"
#include <string>

Transaction::Transaction(const std::string& t, const std::string& f, const std::string& tt, uint64_t a)
    : type(t), from(f), to(tt), amount(a) {}

std::string Transaction::hash() const {
    return sha256(type + from + to + std::to_string(amount));
}
