#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "block.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    std::vector<std::pair<std::string, uint64_t>> validators;
    uint64_t minStakeAmount;

public:
    Blockchain(int diff = 2, uint64_t minStake = 1000);

    void createGenesisBlock();
    Block& getLatestBlock();
    void addBlock(const std::string& data, const std::string& validatorAddress, uint64_t stake);
    bool isValidValidator(const std::string& address, uint64_t stake) const;
    void registerValidator(const std::string& address, uint64_t stake);
    bool isChainValid();
    void printChain() const;
};
