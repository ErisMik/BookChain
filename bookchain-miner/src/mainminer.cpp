#include "mainpeers.hpp"

#include "block.hpp"
#include "difficulty.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "utils.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

namespace bookchain {

void minerMainLoop(const sharedTSQueue<std::string>& dataQueue) {
    std::cout << "Launching miner thread" << std::endl;

    std::random_device randomDevice;
    std::uniform_int_distribution<int64_t> randomDistribution(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    Bloockchain bloockchain;

    if (bloockchain.height() == 0) {
        std::cout << "No chain found, creating a new chain" << std::endl;
        Bloock genesisBloock("P R E V H A S H", "S E E D H A S H", 0);
        genesisBloock.writeData("G E N E S I S");
        bloockchain.append(genesisBloock);
    }

    while (true) {
        std::string data;
        if (!dataQueue->empty()) {
            data = dataQueue->front();
        }

        const int miningHeight = bloockchain.height() + 1;
        Bloock miningBloock(bloockchain.latest().blockHash(), "S E E D H A S H", miningHeight);

        while (verifyBlockDifficulty(miningBloock)) {
            miningBloock.setNonce(randomDistribution(randomDevice));

            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // SHA1 is too easy, need to nerf it until proper POW is added
        }

        std::cout << "Block " << miningHeight << " found with hash: " << utils::hexifystring(miningBloock.blockHash()) << std::endl;

        Bloock latestBloock = bloockchain.latest();
        if (verifyPair(latestBloock, miningBloock)) {
            std::cout << "Block " << utils::hexifystring(miningBloock.blockHash()) << " added to chain!" << std::endl;
            bloockchain.append(miningBloock);
        } else {
            std::cout << "Block " << utils::hexifystring(miningBloock.blockHash()) << " no longer valid" << std::endl;
        }
    }

    std::cout << "Miner thread stopped" << std::endl;
}

}  // namespace bookchain
