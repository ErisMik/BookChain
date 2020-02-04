#include "block.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "http/server.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include "storage.hpp"
#include "utils.hpp"
#include <iostream>
#include <thread>

void launchMiner(bookchain::sharedTSQueue<bookchain::Peer> peerQueue, bookchain::sharedTSQueue<std::string> /* dataQueue */) {
    std::cout << "Launching miner thread" << std::endl;

    std::cout << "Creating new bloock" << std::endl;
    bookchain::Bloock testBloock("i", "i", 0);
    testBloock.writeData("i");
    std::cout << bookchain::utils::hexifystring(testBloock.blockHash()) << std::endl;
    std::cout << bookchain::utils::hexifystring(testBloock.prevHash()) << std::endl;

    bookchain::Bloock testBloockTwo(testBloock.block());
    std::cout << bookchain::utils::hexifystring(testBloockTwo.blockHash()) << std::endl;
    std::cout << bookchain::utils::hexifystring(testBloockTwo.prevHash()) << std::endl;

    bookchain::Bloockchain bloockchain;
    bloockchain.purge();
    bloockchain.append(testBloock);

    constexpr int testBloockchainLength = 100;
    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "i", i);
        newBloock.setNonce(i);
        bloockchain.append(newBloock);
    }

    std::cout << bookchain::verifyChain(bloockchain) << " " << bloockchain.height() << " " << sizeof(bookchain::Bloock) << std::endl;

    bookchain::Bloockchain bloockchain2;

    std::cout << bookchain::verifyChain(bloockchain2) << std::endl;

    std::cout << bloockchain.height() << " " << bloockchain2.height() << std::endl;

    constexpr unsigned int testBlockHeight = 5U;
    bookchain::Bloock fifthBlock = bookchain::storage::getBlockByHeight(testBlockHeight, &bookchain::bloockchainFilename[0]);
    std::cout << bookchain::utils::hexifystring(fifthBlock.blockHash()) << std::endl;
    std::cout << bookchain::utils::hexifystring(bloockchain.bloock(testBlockHeight).blockHash()) << std::endl;

    std::cout << "Miner thread stopped" << std::endl;

    std::cout << "Looping!" << std::endl;
    while (true) {
        if (!peerQueue->empty()) {
            bookchain::Peer peer = peerQueue->pop();
            std::cout << "GOT PEER WITH IP " << peer.ipAddress() << std::endl;
        }
    }
}

void launchNode(bookchain::sharedTSQueue<bookchain::Peer> peerQueue, bookchain::sharedTSQueue<std::string> dataQueue) {
    std::cout << "Launching node thread" << std::endl;

    bookchain::http::startNodeServer(peerQueue, dataQueue);

    std::cout << "Node thread stopped" << std::endl;
}

int main(int /*argc*/, const char* /*argv*/[]) {
    auto peerQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Peer>>();
    auto dataQueue = std::make_shared<bookchain::ThreadsafeQueue<std::string>>();

    std::thread minerThread(launchMiner, peerQueue, dataQueue);
    std::thread nodeThread(launchNode, peerQueue, dataQueue);

    minerThread.join();
    nodeThread.join();
}
