#pragma once
#include <vector>
#include <string>
#include "block.h"
#include "token.h"
#include "transaction.h"

class DSL {
private:
    Token& token;
    std::vector<Block>& blockchain;
    std::vector<Transaction> tempTransactions;

public:
    DSL(Token& t, std::vector<Block>& bc) : token(t), blockchain(bc) {}
    void executeFile(const std::string& filename);
};
