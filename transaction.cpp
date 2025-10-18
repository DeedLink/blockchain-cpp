#include "transaction.h"
#include "sha256.h"

std::string Transaction::hash() const {
    return sha256(data);
}
