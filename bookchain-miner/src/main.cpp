#include "block.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "http/server.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include "storage.hpp"
#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

void launchMiner(const bookchain::sharedTSQueue<std::string>& dataQueue) {
    std::cout << "Launching miner thread" << std::endl;

    std::random_device randomDevice;
    std::uniform_int_distribution<int64_t> randomDistribution(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    bookchain::Bloockchain bloockchain;

    if (bloockchain.height() == 0) {
        std::cout << "No chain found, creating a new chain" << std::endl;
        bookchain::Bloock genesisBloock("P R E V H A S H", "S E E D H A S H", 0);
        genesisBloock.writeData("G E N E S I S");
        bloockchain.append(genesisBloock);
    }

    while (true) {
        std::string data;
        if (!dataQueue->empty()) {
            data = dataQueue->front();
        }

        const int miningHeight = bloockchain.height() + 1;
        bookchain::Bloock miningBloock(bloockchain.latest().blockHash(), "S E E D H A S H", miningHeight);

        while (miningBloock.blockHash()[0] != 'E') {
            miningBloock.setNonce(randomDistribution(randomDevice));

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // SHA1 is too easy, need to nerf it until proper POW is added
        }

        std::cout << "Block " << miningHeight << " found with hash: " << bookchain::utils::hexifystring(miningBloock.blockHash()) << std::endl;

        bookchain::Bloock latestBloock = bloockchain.latest();
        if (bookchain::verifyPair(latestBloock, miningBloock)) {
            std::cout << "Block " << bookchain::utils::hexifystring(miningBloock.blockHash()) << " added to chain!" << std::endl;
            bloockchain.append(miningBloock);
        } else {
            std::cout << "Block " << bookchain::utils::hexifystring(miningBloock.blockHash()) << " no longer valid" << std::endl;
        }
    }

    std::cout << "Miner thread stopped" << std::endl;
}

void launchPeer(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue) {
    std::cout << "Launching peer thread" << std::endl;

    bookchain::PeersList peersList;

    while (true) {
        if (!peerQueue->empty()) {
            bookchain::Peer peer = peerQueue->pop();
            peer.makeActive();
            std::cout << "GOT PEER WITH IP " << peer.ipAddress() << std::endl;
            peersList.addPeer(peer);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Peer thread stopped" << std::endl;
}

void launchNode(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue, const bookchain::sharedTSQueue<std::string>& dataQueue) {
    std::cout << "Launching node thread" << std::endl;

    bookchain::http::startNodeServer(peerQueue, dataQueue);

    std::cout << "Node thread stopped" << std::endl;
}

int main(int /*argc*/, const char* /*argv*/[]) {
    auto peerQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Peer>>();
    auto dataQueue = std::make_shared<bookchain::ThreadsafeQueue<std::string>>();

    std::thread minerThread(launchMiner, dataQueue);
    std::thread peerThread(launchPeer, peerQueue);
    std::thread nodeThread(launchNode, peerQueue, dataQueue);

    minerThread.join();
    peerThread.join();
    nodeThread.join();
}
