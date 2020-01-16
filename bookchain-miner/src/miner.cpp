#include "block.hpp"
#include "chain.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    using namespace bookchain;

    std::cout << "Hello world!" << std::endl;
    std::cout << "Creating new bloock" << std::endl;

    Bloock testBloock("i", "i", 0);
    testBloock.writeData("i");
    std::cout << utils::hexifystring(testBloock.blockHash()) << std::endl;

    Bloock testBloockTwo(testBloock.block());
    std::cout << utils::hexifystring(testBloockTwo.blockHash()) << std::endl;

    std::vector<Bloock> bloockChain;
    bloockChain.push_back(testBloock);

    for (int i = 1; i < 100; ++i) {
        Bloock newBloock(bloockChain.back().blockHash(), "i", i);
        newBloock.setNonce(i);
        bloockChain.push_back(newBloock);
    }

    verifyChain(bloockChain);
}
