#include "http/server.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include "mainminer.hpp"
#include "mainpeers.hpp"
#include <iostream>
#include <thread>
#include <string>

void launchNode(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue, const bookchain::sharedTSQueue<std::string>& dataQueue) {
    std::cout << "Launching node thread" << std::endl;

    bookchain::http::startNodeServer(peerQueue, dataQueue);

    std::cout << "Node thread stopped" << std::endl;
}

int main(int /*argc*/, const char* /*argv*/[]) {
    auto peerQueue = std::make_shared<bookchain::ThreadsafeQueue<bookchain::Peer>>();
    auto dataQueue = std::make_shared<bookchain::ThreadsafeQueue<std::string>>();

    std::thread minerThread(bookchain::minerMainLoop, dataQueue);
    std::thread peerThread(bookchain::peerMainLoop, peerQueue);
    std::thread nodeThread(launchNode, peerQueue, dataQueue);

    minerThread.join();
    peerThread.join();
    nodeThread.join();
}
