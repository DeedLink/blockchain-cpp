#include <cstdint>
#include "token.h"

void Token::mint(const std::string& address, uint64_t amount) {
    balances[address] += amount;
}

bool Token::transfer(const std::string& from, const std::string& to, uint64_t amount) {
    if (balances[from] < amount) return false;
    balances[from] -= amount;
    balances[to] += amount;
    return true;
}

uint64_t Token::balanceOf(const std::string& address) const {
    auto it = balances.find(address);
    if (it == balances.end()) return 0;
    return it->second;
}
