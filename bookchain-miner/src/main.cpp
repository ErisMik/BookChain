#include "http/server.hpp"
#include "job.hpp"
#include "mainminer.hpp"
#include "mainpeers.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include <csignal>
#include <iostream>
#include <string>
#include <thread>

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void launchNode(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue, const bookchain::sharedTSQueue<std::string>& dataQueue, const bookchain::sharedTSQueue<bookchain::Job>& jobQueue) {
    std::cout << "Launching node thread" << std::endl;

    bookchain::http::startNodeServer(peerQueue, dataQueue, jobQueue);

    std::cout << "Node thread stopped" << std::endl;
}

int main(int /*argc*/, const char* /*argv*/[]) {
    signal(SIGINT, signalHandler);
    signal(SIGKILL, signalHandler);

    auto peerQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Peer>>();
    auto dataQueue = std::make_shared<bookchain::ThreadsafeQueue<std::string>>();
    auto jobQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Job>>();

    std::thread minerThread(bookchain::minerMainLoop, jobQueue);
    std::thread peerThread(bookchain::peerMainLoop, peerQueue, dataQueue, jobQueue);
    std::thread nodeThread(launchNode, peerQueue, dataQueue, jobQueue);

    minerThread.join();
    peerThread.join();
    nodeThread.join();
}
