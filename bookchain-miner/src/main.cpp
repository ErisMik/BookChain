#include "http/server.hpp"
#include "job.hpp"
#include "mainminer.hpp"
#include "mainpeers.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include <csignal>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void launchNode(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue, const bookchain::sharedTSQueue<bookchain::Job>& jobQueue) {
    std::cout << "Launching node thread" << std::endl;

    bookchain::http::startNodeServer(peerQueue, jobQueue);

    std::cout << "Node thread stopped" << std::endl;
}

int main(int argc, const char* argv[], const char* /*envp*/[]) {
    signal(SIGINT, signalHandler);
    signal(SIGKILL, signalHandler);

    std::unordered_set<std::string> argFlags;
    for (int i = 1; i < argc; ++i) {
        argFlags.emplace(argv[i]);
    }

    auto peerQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Peer>>();
    auto jobQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Job>>();

    std::vector<std::shared_ptr<std::thread>> threads;

    if (argFlags.count("nominer") == 0) {
        auto minerThread = std::make_shared<std::thread>(bookchain::minerMainLoop, jobQueue);
        threads.push_back(minerThread);
    }
    if (argFlags.count("nosync") == 0) {
        auto peerThread = std::make_shared<std::thread>(bookchain::peerMainLoop, peerQueue, jobQueue);
        threads.push_back(peerThread);

        auto nodeThread = std::make_shared<std::thread>(launchNode, peerQueue, jobQueue);
        threads.push_back(nodeThread);
    }

    for (auto threadPtr : threads) {
        threadPtr->join();
    }
}
