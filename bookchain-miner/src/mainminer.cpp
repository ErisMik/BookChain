#include "block.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "difficulty.hpp"
#include "job.hpp"
#include "mainpeers.hpp"
#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

namespace bookchain {

void minerMainLoop(const sharedTSQueue<Job>& jobQueue) {
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
        Job currentJob = Job::invalidJob();
        std::string data;

        if (!jobQueue->empty()) {
            currentJob = jobQueue->front();
            data = currentJob.data();
            std::cout << "Starting block with data " << data << std::endl;
        }

        const int miningHeight = bloockchain.height() + 1;
        Bloock miningBloock(bloockchain.latest().blockHash(), "S E E D H A S H", miningHeight);
        miningBloock.writeData(data);

        while (!verifyBlockDifficulty(miningBloock)) {
            miningBloock.setNonce(randomDistribution(randomDevice));
            // TODO(Eric Mikulin): Add check (flag?) to escape if data is not valid anymore
        }

        std::cout << "Block " << miningHeight << " found with hash: " << utils::hexifystring(miningBloock.blockHash()) << std::endl;

        Bloock latestBloock = bloockchain.latest();
        if (verifyPair(latestBloock, miningBloock)) {
            std::cout << "Block " << utils::hexifystring(miningBloock.blockHash()) << " added to chain!" << std::endl;
            bloockchain.append(miningBloock);
            if (jobQueue->front().id() == currentJob.id()) {
                jobQueue->pop();
            }
        } else {
            std::cout << "Block " << utils::hexifystring(miningBloock.blockHash()) << " no longer valid" << std::endl;
        }
    }

    std::cout << "Miner thread stopped" << std::endl;
}

}  // namespace bookchain
