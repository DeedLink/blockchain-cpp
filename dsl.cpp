#include "dsl.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DSL::executeFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open DSL file: " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));

        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "VALIDATOR") {
            std::string name; uint64_t stake;
            iss >> name >> stake;
            std::cout << "Validator registered: " << name << " with stake " << stake << "\n";
        } else if (cmd == "MINT") {
            std::string to; uint64_t amount;
            iss >> to >> amount;
            token.mint(to, amount);
            std::cout << "Minted " << amount << " to " << to << "\n";
        } else if (cmd == "TRANSFER") {
            std::string from, to; uint64_t amount;
            iss >> from >> to >> amount;
            token.transfer(from, to, amount);
            std::cout << "Transferred " << amount << " from " << from << " to " << to << "\n";
        } else if (cmd == "BLOCK") {
            std::string data;
            std::getline(iss, data);
            data.erase(0, data.find_first_not_of(" \t"));
            std::string prevHash = blockchain.empty() ? "0" : blockchain.back().hash;
            Block newBlock(blockchain.size(), prevHash, "DSL block", data, "", 0, "DSL", 0);
            newBlock.mine(2);
            blockchain.push_back(newBlock);
            std::cout << "Block added: " << data << "\n";
        } else {
            std::cerr << "Unknown command: " << cmd << "\n";
        }
    }
}
