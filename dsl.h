#pragma once
#include <vector>
#include <string>
#include "block.h"
#include "token.h"

class DSL {
private:
    Token& token;
    std::vector<Block>& blockchain;

public:
    DSL(Token& t, std::vector<Block>& bc) : token(t), blockchain(bc) {}
    void executeFile(const std::string& filename);
};
