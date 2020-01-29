#include "block.hpp"
#include "chain.hpp"
#include "http/server.hpp"
#include "storage.hpp"
#include "utils.hpp"
#include <iostream>

int main(int /*argc*/, const char* /*argv*/[]) {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Creating new bloock" << std::endl;

    bookchain::Bloock testBloock("i", "i", 0);
    testBloock.writeData("i");
    std::cout << bookchain::utils::hexifystring(testBloock.blockHash()) << std::endl;
    std::cout << bookchain::utils::hexifystring(testBloock.prevHash()) << std::endl;

    bookchain::Bloock testBloockTwo(testBloock.block());
    std::cout << bookchain::utils::hexifystring(testBloockTwo.blockHash()) << std::endl;
    std::cout << bookchain::utils::hexifystring(testBloockTwo.prevHash()) << std::endl;

    std::vector<bookchain::Bloock> bloockChain;
    bloockChain.push_back(testBloock);

    constexpr int testBlockChainLength = 100;
    for (int i = 1; i < testBlockChainLength; ++i) {
        bookchain::Bloock newBloock(bloockChain.back().blockHash(), "i", i);
        newBloock.setNonce(i);
        bloockChain.push_back(newBloock);
    }

    bookchain::saveChain(bloockChain);

    std::cout << bookchain::verifyChain(bloockChain) << " " << bloockChain.size() << " " << sizeof(bookchain::Bloock) << std::endl;

    std::vector<bookchain::Bloock> bloockChain2 = bookchain::getFullChain();

    std::cout << bookchain::verifyChain(bloockChain2) << std::endl;

    std::cout << bloockChain.size() << " " << bloockChain2.size() << std::endl;

    constexpr unsigned int testBlockHeight = 5U;
    bookchain::Bloock fifthBlock = bookchain::getBlockByHeight(testBlockHeight);
    std::cout << bookchain::utils::hexifystring(fifthBlock.blockHash()) << std::endl;

    bookchain::http::startMinerHttpServer();
}
