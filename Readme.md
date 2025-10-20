# blockchain-cpp

A minimal C++ Proof-of-Stake style blockchain prototype.  
Implements blocks with transactions, Merkle root calculation, mining (adjustable difficulty), validator registration and basic stake verification.

## Features
- Block structure with index, timestamp, previous hash, Merkle root, nonce, stake and validator signature
- Merkle root computation from block transactions
- Simple mining (proof-of-work style) for demonstrative purposes
- Validator registration and basic stake checks (PoS concept)
- Chain validation and printing utilities

## Repository layout
- block.cpp / block.h        — Block implementation (Merkle root, hash, mine, validation)
- chain.cpp / chain.h?       — Blockchain class (chain management, validators)
- transaction.cpp / transaction.h? — Transaction representation (used by Block)
- sha256.h / sha256.cpp      — SHA-256 hash implementation (required)
- main.cpp (optional)        — Example usage / test program

Files marked with `?` may need to be added/adjusted according to your project.

## Prerequisites
- Linux
- g++ with C++11 or later
- CMake (optional)

## Build (simple g++)
From the project root (adjust filenames if you used different names):
```bash
g++ -std=c++11 -O2 main.cpp block.cpp chain.cpp transaction.cpp sha256.cpp -o blockchain
```
If you only have a minimal test main, compile the files you actually have:
```bash
g++ -std=c++11 block.cpp chain.cpp sha256.cpp -o blockchain
```

## Run
```bash
./blockchain
```
(Example behaviour depends on the provided `main.cpp`. Typical output: genesis block created, additional blocks mined, chain printed.)

## Usage notes
- Ensure `transaction.h` defines a `Transaction` class with a `std::string hash() const` method used by `Block::calculateMerkleRoot()`.
- `sha256.h`/`.cpp` must provide a `std::string sha256(const std::string&)` function.
- Mining difficulty is adjustable via the `Blockchain` constructor or setter.
- Validator registration must be called before adding blocks with a validator stake.