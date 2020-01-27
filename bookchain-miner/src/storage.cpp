#include "block.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace bookchain {

void saveChain(std::vector<Bloock> bloockChain, const std::string& filename) {
    std::ofstream blockchainFile(filename, std::ios::out | std::ios::binary);

    for (auto& bloock : bloockChain) {
        blockchainFile.write(reinterpret_cast<char*>(&bloock), sizeof(bloock));  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }

    blockchainFile.close();
}

std::vector<Bloock> getFullChain(const std::string& filename) {
    std::ifstream blockchainFile(filename, std::ios::in | std::ios::binary);
    std::vector<Bloock> bloockChain;

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }
    blockchainFile.seekg(0);

    Bloock bloock = {};
    while (blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeof(bloock))) {  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        bloockChain.push_back(bloock);
    }

    return bloockChain;
}

Bloock getBlockByHeight(unsigned int blockHeight, const std::string& filename) {
    std::ifstream blockchainFile(filename, std::ios::in | std::ios::binary);

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }
    blockchainFile.seekg(0);

    Bloock bloock = {};
    blockchainFile.seekg(blockHeight * sizeof(bloock));
    blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeof(bloock));  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    // Verify
    if (bloock.blockHeight() != blockHeight) {
        std::cout << "Unable to find correct block" << std::endl;
    }

    return bloock;
}

}  // namespace bookchain
