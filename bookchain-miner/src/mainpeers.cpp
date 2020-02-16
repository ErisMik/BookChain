#include "mainpeers.hpp"
#include "chain.hpp"
#include "utils.hpp"
#include "version.hpp"

#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

namespace bookchain {

size_t stringWriteCallback(char* ptr, size_t size, size_t nmemb, std::string* userdata) {
    size_t realSize = size * nmemb;
    userdata->append(ptr, realSize);

    return realSize;
}

std::string getRequest(const std::string& url) {
    CURL* curl = nullptr;
    CURLcode response;
    std::string returnString;

    curl = curl_easy_init();
    if (curl != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stringWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnString);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) {
            returnString = "";
        }

        curl_easy_cleanup(curl);
    }

    return (returnString.empty()) ? "{}" : returnString;
}

std::string postRequest(const std::string& url, const std::string& payload) {
    CURL* curl = nullptr;
    CURLcode response;
    std::string returnString;

    curl = curl_easy_init();
    ;
    if (curl != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stringWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnString);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) {
            returnString = "";
        }

        curl_easy_cleanup(curl);
    }

    return (returnString.empty()) ? "{}" : returnString;
}

void discoverInitialPeers(PeersList& peersList) {
    const std::array<std::string, 1> peerHints = {"127.0.0.1:8000"};

    auto discoverPeer = [&peersList](const std::string& peerHint) {
        std::string findResponse = getRequest(peerHint);
        auto findResponseJson = nlohmann::json::parse(findResponse);
        if (findResponseJson.count("identifier") == 0) {
            // Peer gave response but not the one we expect
            std::cout << "Peerhint is not a bookchain instance" << std::endl;
            return;
        }

        std::string peersURL = peerHint + "/peers/";
        std::string peersResponse = getRequest(peersURL);
        auto peersResponseJson = nlohmann::json::parse(peersResponse);
        for (auto& peerJson : peersResponseJson) {
            Peer peer(peerJson["ipAddress"]);
            peersList.addPeer(peer);
        }

        std::string peerLinkURL = peerHint + "/peers/link/";
        nlohmann::json peerLinkJson = {
            {"identifier", utils::identifierHash()},
            {"version", versionString},
            {"ipAddress", "127.0.0.1"}  // TODO(Eric Mikulin): Get the IP from the request
        };
        std::string peerLinkResponse = postRequest(peerLinkURL, peerLinkJson.dump());
        auto peerLinkResponseJson = nlohmann::json::parse(peerLinkResponse);
        if (peerLinkResponseJson.count("success") == 0) {
            std::cout << "Failed to link with peer" << std::endl;
            return;
        }

        std::cout << "Done connecting to " << peerHint << std::endl;
    };

    for (auto& peerHint : peerHints) {
        discoverPeer(peerHint);
    }

    // TODO(Eric Mikulin): If the hints don't work, start searching
}

void syncBlocksWithPeers(PeersList& peersList) {
    auto peers = peersList.activePeers();
    Bloockchain bloockchain;

    for (auto& peer : peers) {
        std::string blockLatestURL = peer.ipAddress() + "/blocks/latest/";
        std::string blockLatestResponse = getRequest(blockLatestURL);
        auto blockLatestJson = nlohmann::json::parse(blockLatestResponse);

        if (blockLatestJson["blockHeight"] > bloockchain.height()) {
            // TODO(Eric Mikulin): Merge the chains
        }
    }
}

void syncPeersWithPeers(PeersList& peersList) {
    auto peers = peersList.activePeers();

    for (auto& peer : peers) {
        std::string peersURL = peer.ipAddress() + "/peers/";
        std::string peersResponse = getRequest(peersURL);
        auto peersResponseJson = nlohmann::json::parse(peersResponse);
        for (auto& peerJson : peersResponseJson) {
            Peer peer(peerJson["ipAddress"]);
            peersList.addPeer(peer);
        }
    }
}

void syncDataWithPeers(PeersList& peersList) {
    // TODO(Eric Mikulin)
}

void handleNewPeers(PeersList& peersList, const sharedTSQueue<Peer>& peerQueue) {
    while (!peerQueue->empty()) {
        Peer peer = peerQueue->pop();
        peer.makeActive();
        std::cout << "GOT PEER WITH IP " << peer.ipAddress() << std::endl;
        peersList.addPeer(peer);
    }
}

void peerMainLoop(const sharedTSQueue<Peer>& peerQueue) {
    std::cout << "Launching peer thread" << std::endl;

    PeersList peersList;

    // TODO(Eric Mikulin): TESTING - Prepopulate the peerslist
    peersList.addPeer(Peer("TestingIp1"));
    peersList.addPeer(Peer("TestingIp2"));
    peersList.addPeer(Peer("TestingIp3"));

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));  // TODO(Eric Mikulin): TESTING - Give server thread time to start
    discoverInitialPeers(peersList);

    while (true) {
        syncBlocksWithPeers(peersList);
        syncPeersWithPeers(peersList);
        syncDataWithPeers(peersList);
        handleNewPeers(peersList, peerQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Peer thread stopped" << std::endl;
}

}  // namespace bookchain
