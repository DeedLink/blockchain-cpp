class Block {
    public:
        uint64_t index;
        std::string previousHash;
        std::string timestamp;
        std::string data;
        std::string hash;
        uint64_t nonce;

        std: string validatorSignature;
        uint64_t stake;

        Block(uint64_t idx, const std::string& prevHash, const std::string& time, const std::string& blockData, 
              const std::string& blockHash, uint64_t blockNonce, const std::string& signature, uint64_t blockStake)
            : index(idx), previousHash(prevHash), timestamp(time), data(blockData), hash(blockHash), 
              nonce(blockNonce), validatorSignature(signature), stake(blockStake) {}
            
        std::string calculateHash() const {
            std::stringstream ss;
            ss << index << timestamp << previousHash << merkleRoot << nonce << stake;
            return sha256(ss.str());
        }

        std::string calculateMerkleRoot() const {
            if (transactions.empty()) return sha256("empty");
            
            std::vector<std::string> hashes;
            for (const auto& tx : transactions) {
                hashes.push_back(tx.hash());
            }

            while (hashes.size() > 1) {
                std::vector<std::string> newLevel;
                for (size_t i = 0; i < hashes.size(); i += 2) {
                    if (i + 1 < hashes.size()) {
                        newLevel.push_back(sha256(hashes[i] + hashes[i + 1]));
                    } else {
                        newLevel.push_back(hashes[i]);
                    }
                }
                hashes = newLevel;
            }
            return hashes[0];
        }
        
        void mine(int difficulty) {
            std::string target(difficulty, '0');
            do {
                nonce++;
                hash = calculateHash();
            } while (hash.substr(0, difficulty) != target);
            
            std::cout << "Block mined: " << hash << " (nonce: " << nonce << ")\n";
        }
        
        bool isValid() const {
            return hash == calculateHash() && merkleRoot == calculateMerkleRoot();
        }
}