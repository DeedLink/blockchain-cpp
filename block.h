#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "transaction.h"

class Block {
public:
    uint64_t index;
    std::string previousHash;
    std::string timestamp;
    std::string data;
    std::string hash;
    uint64_t nonce;
    std::string validatorSignature;
    uint64_t stake;
    std::string merkleRoot;
    std::vector<Transaction> transactions;

    Block(uint64_t idx=0, const std::string& prevHash="", const std::string& time="",
          const std::string& blockData="", const std::string& blockHash="", uint64_t blockNonce=0,
          const std::string& signature="", uint64_t blockStake=0);

    std::string calculateMerkleRoot() const;
    std::string calculateHash();
    void mine(int difficulty);
    bool isValid();
};
