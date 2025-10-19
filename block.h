#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "transaction.h"
#include "json.hpp"

using json = nlohmann::json;

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

    json to_json() const {
        json txs = json::array();
        for (const auto& tx : transactions) {
            txs.push_back({
                {"type", tx.type},
                {"from", tx.from},
                {"to", tx.to},
                {"amount", tx.amount},
                {"hash", tx.hash()}
            });
        }
        return json{
            {"index", index},
            {"previousHash", previousHash},
            {"timestamp", timestamp},
            {"data", data},
            {"hash", hash},
            {"nonce", nonce},
            {"validator", validatorSignature},
            {"stake", stake},
            {"transactions", txs}
        };
    }
};
