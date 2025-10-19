#include <vector>
#include <fstream>
#include <iostream>
#include "block.h"
#include "token.h"
#include "dsl.h"
#include "json.hpp"

using json = nlohmann::json;

void saveBlockchain(const std::vector<Block>& chain) {
    json j;
    for (auto& block : chain) j.push_back(block.to_json());
    std::ofstream file("web/blockchain.json");
    file << std::setw(4) << j;
}

int main() {
    std::vector<Block> blockchain;
    blockchain.push_back(Block(0, "0", "Genesis Block", "Genesis Block"));

    Token token;
    DSL dsl(token, blockchain);

    dsl.executeFile("mycontract.maz");
    saveBlockchain(blockchain);

    std::cout << "Blockchain saved to blockchain.json\n";
    return 0;
}
