#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include "block.h"
#include "transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    std::vector<std::pair<std::string, uint64_t>> validators;
    uint64_t minStakeAmount;

public:
    Blockchain(int diff = 4, uint64_t minStake = 1000) : difficulty(diff), minStakeAmount(minStake) {
        createGenesisBlock();
    }

    void createGenesisBlock() {
        std::time_t now = std::time(0);
        std::string timestamp = std::ctime(&now);
        Block genesis(0, "0", timestamp, "Genesis Block", "", 0, "", 0);
        genesis.mine(difficulty);
        chain.push_back(genesis);
    }

    Block& getLatestBlock() {
        return chain.back();
    }

    void addBlock(const std::string& data, const std::string& validatorAddress, uint64_t stake) {
        if (!isValidValidator(validatorAddress, stake)) {
            throw std::runtime_error("Invalid validator or insufficient stake");
        }

        std::time_t now = std::time(0);
        std::string timestamp = std::ctime(&now);
        
        Block newBlock(
            chain.size(),
            getLatestBlock().hash,
            timestamp,
            data,
            "",
            0,
            validatorAddress,
            stake
        );

        newBlock.mine(difficulty);
        chain.push_back(newBlock);
    }

    bool isValidValidator(const std::string& address, uint64_t stake) const {
        if (stake < minStakeAmount) return false;
        
        for (const auto& validator : validators) {
            if (validator.first == address && validator.second >= stake) {
                return true;
            }
        }
        return false;
    }

    void registerValidator(const std::string& address, uint64_t stake) {
        if (stake < minStakeAmount) {
            throw std::runtime_error("Insufficient stake amount");
        }
        
        for (auto& validator : validators) {
            if (validator.first == address) {
                validator.second = stake;
                return;
            }
        }
        
        validators.push_back(std::make_pair(address, stake));
    }

    bool isChainValid() const {
        for (size_t i = 1; i < chain.size(); i++) {
            const Block& currentBlock = chain[i];
            const Block& previousBlock = chain[i - 1];

            if (!currentBlock.isValid()) {
                return false;
            }

            if (currentBlock.previousHash != previousBlock.hash) {
                return false;
            }

            if (!isValidValidator(currentBlock.validatorSignature, currentBlock.stake)) {
                return false;
            }
        }
        return true;
    }

    void printChain() const {
        for (const auto& block : chain) {
            std::cout << "\nBlock Index: " << block.index
                      << "\nTimestamp: " << block.timestamp
                      << "\nData: " << block.data
                      << "\nHash: " << block.hash
                      << "\nPrevious Hash: " << block.previousHash
                      << "\nValidator: " << block.validatorSignature
                      << "\nStake: " << block.stake
                      << "\n-----------------------" << std::endl;
        }
    }

    size_t getChainLength() const {
        return chain.size();
    }

    int getDifficulty() const {
        return difficulty;
    }

    void setDifficulty(int diff) {
        difficulty = diff;
    }

    uint64_t getMinStakeAmount() const {
        return minStakeAmount;
    }

    const std::vector<std::pair<std::string, uint64_t>>& getValidators() const {
        return validators;
    }
};