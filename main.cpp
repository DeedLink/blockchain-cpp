#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include "json.hpp"

using json = nlohmann::json;

struct Block {
    int index;
    std::string data;
    std::string previousHash;
    std::string hash;

    static std::string sha256(const std::string& str) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);
        std::stringstream ss;
        for (auto i : hash)
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)i;
        return ss.str();
    }

    Block(int idx, const std::string& dat, const std::string& prev)
        : index(idx), data(dat), previousHash(prev) {
        hash = sha256(std::to_string(index) + data + previousHash);
    }

    json to_json() const {
        return json{
            {"index", index},
            {"data", data},
            {"hash", hash},
            {"previousHash", previousHash}
        };
    }
};

std::vector<Block> blockchain;

void saveBlockchain(const std::vector<Block>& chain) {
    json j;
    for (const auto& block : chain)
        j.push_back(block.to_json());

    std::ofstream file("web/blockchain.json");
    file << std::setw(4) << j;
    file.close();
}

int main() {
    blockchain.push_back(Block(0, "Genesis Block", "0"));
    saveBlockchain(blockchain);

    blockchain.push_back(Block(1, "Block 1 Data", blockchain.back().hash));
    saveBlockchain(blockchain);

    blockchain.push_back(Block(2, "Block 2 Data", blockchain.back().hash));
    saveBlockchain(blockchain);

    return 0;
}
