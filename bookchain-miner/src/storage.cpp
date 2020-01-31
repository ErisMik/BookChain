#include "block.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace bookchain::storage {

constexpr size_t sizeofBloock = sizeof(Bloock);

void purgeChain(const std::string& filename) {
    std::ofstream blockchainFile(filename, std::ios::binary);
    blockchainFile.close();
}

void dumpChain(std::vector<Bloock> bloockChain, const std::string& filename) {
    std::ofstream blockchainFile(filename, std::ios::binary);

    for (auto& bloock : bloockChain) {
        blockchainFile.write(reinterpret_cast<char*>(&bloock), sizeofBloock);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }

    blockchainFile.close();
}

std::vector<Bloock> getChain(const std::string& filename) {
    std::ifstream blockchainFile(filename, std::ios::binary);
    std::vector<Bloock> bloockChain;

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }
    blockchainFile.seekg(0);

    Bloock bloock = {};
    while (blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeofBloock)) {  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        bloockChain.push_back(bloock);
    }

    blockchainFile.close();
    return bloockChain;
}

void appendChain(Bloock bloock, const std::string& filename) {
    std::ofstream blockchainFile(filename, std::ios::ate | std::ios::app | std::ios::binary);

    blockchainFile.write(reinterpret_cast<char*>(&bloock), sizeofBloock);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    blockchainFile.close();
}

Bloock getBlockByHeight(unsigned int blockHeight, const std::string& filename) {
    std::ifstream blockchainFile(filename, std::ios::in | std::ios::binary);

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }
    blockchainFile.seekg(0);

    Bloock bloock = {};
    blockchainFile.seekg(blockHeight * sizeofBloock);
    blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeofBloock);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    // Verify
    if (bloock.blockHeight() != blockHeight) {
        std::cout << "Unable to find correct block" << std::endl;
    }

    blockchainFile.close();
    return bloock;
}

Bloock getBlockLatest(const std::string& filename) {
    std::ifstream blockchainFile(filename, std::ios::binary);

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }

    Bloock bloock = {};
    blockchainFile.seekg(-sizeofBloock, std::ifstream::end);
    blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeofBloock);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    blockchainFile.close();
    return bloock;
}

int getChainHeight(const std::string& filename) {
    Bloock bloock = getBlockLatest(filename);

    return bloock.blockHeight();
}

}  // namespace bookchain::storage
