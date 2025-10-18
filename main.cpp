#include "blockchain.h"
#include <iostream>

int main() {
    Blockchain bc;
    bc.registerValidator("Validator1", 1500);

    bc.addBlock("First Block", "Validator1", 1500);
    bc.addBlock("Second Block", "Validator1", 1500);

    std::cout << "\nBlockchain:\n";
    bc.printChain();

    std::cout << "\nIs blockchain valid? " << (bc.isChainValid() ? "Yes" : "No") << "\n";

    return 0;
}
