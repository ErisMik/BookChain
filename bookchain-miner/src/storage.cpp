#include "block.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace bookchain {

void saveChain(std::vector<Bloock> bloockChain, std::string filename) {
    std::ofstream blockchainFile(filename, std::ios::out | std::ios::binary);

    for (size_t i = 0; i < bloockChain.size(); ++i) {
        blockchainFile.write(reinterpret_cast<char*>(&bloockChain[i]), sizeof(bloockChain[i]));
    }

    blockchainFile.close();
}

std::vector<Bloock> getFullChain(std::string filename) {
    std::ifstream blockchainFile(filename, std::ios::in | std::ios::binary);
    std::vector<Bloock> bloockChain;

    if (blockchainFile.fail()) {
        std::cout << "This is the darkest timeline" << std::endl;
    }
    blockchainFile.seekg(0);

    Bloock bloock = {};
    while (blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeof(bloock))) {
        bloockChain.push_back(bloock);
    }

    return bloockChain;
}

// std::vector<Bloock> getBlockByHeight(std::string filename) {
//     std::ifstream blockchainFile(filename, std::ios::binary);
//     std::vector<Bloock> bloockChain;

//     while (!blockchainFile) {
//         Bloock bloock;
//         blockchainFile.read(reinterpret_cast<char*>(&bloock), sizeof(bloock));
//         bloockChain.push_back(bloock);
//     }

//     blockchainFile.close();
//     return bloockChain;
// }

}  // namespace bookchain
