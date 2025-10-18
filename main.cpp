#include <iostream>
#include "block.h"
#include "blockchain.cpp"

int main() {
    Blockchain myChain(3, 500);

    myChain.registerValidator("Validator1", 1000);

    myChain.addBlock("First block data", "Validator1", 1000);
    myChain.addBlock("Second block data", "Validator1", 1000);

    myChain.printChain();
    
    if (myChain.isChainValid()) {
        std::cout << "Blockchain is valid!" << std::endl;
    } else {
        std::cout << "Blockchain is NOT valid!" << std::endl;
    }

    return 0;
}
