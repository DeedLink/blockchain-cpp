#include "blockchain.h"
#include <ctime>
#include <iostream>
#include <stdexcept>

Blockchain::Blockchain(int diff, uint64_t minStake) : difficulty(diff), minStakeAmount(minStake) {
    createGenesisBlock();
}

void Blockchain::createGenesisBlock() {
    std::time_t now = std::time(0);
    std::string timestamp = std::ctime(&now);
    Block genesis(0, "0", timestamp, "Genesis Block", "", 0, "", 0);
    genesis.mine(difficulty);
    chain.push_back(genesis);
}

Block& Blockchain::getLatestBlock() { return chain.back(); }

void Blockchain::addBlock(const std::string& data, const std::string& validatorAddress, uint64_t stake) {
    if (!isValidValidator(validatorAddress, stake))
        throw std::runtime_error("Invalid validator or insufficient stake");

    std::time_t now = std::time(0);
    std::string timestamp = std::ctime(&now);

    Block newBlock(chain.size(), getLatestBlock().hash, timestamp, data, "", 0, validatorAddress, stake);
    newBlock.mine(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isValidValidator(const std::string& address, uint64_t stake) const {
    if (stake < minStakeAmount) return false;
    for (const auto& v : validators)
        if (v.first == address && v.second >= stake) return true;
    return false;
}

void Blockchain::registerValidator(const std::string& address, uint64_t stake) {
    if (stake < minStakeAmount) throw std::runtime_error("Insufficient stake");
    for (auto& v : validators) {
        if (v.first == address) { v.second = stake; return; }
    }
    validators.push_back({address, stake});
}

bool Blockchain::isChainValid() {
    for (size_t i = 1; i < chain.size(); i++) {
        Block& curr = chain[i];
        Block& prev = chain[i-1];
        if (!curr.isValid()) return false;
        if (curr.previousHash != prev.hash) return false;
        if (!isValidValidator(curr.validatorSignature, curr.stake)) return false;
    }
    return true;
}

void Blockchain::printChain() const {
    for (const auto& block : chain) {
        std::cout << "\nIndex: " << block.index
                  << "\nTimestamp: " << block.timestamp
                  << "\nData: " << block.data
                  << "\nHash: " << block.hash
                  << "\nPrevHash: " << block.previousHash
                  << "\nValidator: " << block.validatorSignature
                  << "\nStake: " << block.stake
                  << "\n-------------------------\n";
    }
}
