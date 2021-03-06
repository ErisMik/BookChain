#include <catch.hpp>
#include <vector>

#include "block.hpp"
#include "chaintools.hpp"

TEST_CASE("verifyChain returns true if a valid chain is given", "[chain][verifyChain]") {
    bookchain::Bloock genesisBlock("G E N E S I S", "B L O C K", 0);

    bookchain::Bloockchain bloockChain;
    bloockChain.purge();
    bloockChain.append(genesisBlock);

    constexpr int testBloockChainLength = 100;
    for (int i = 1; i < testBloockChainLength; ++i) {
        bookchain::Bloock newBloock(bloockChain.latest().blockHash(), "B L O C K", i);
        newBloock.setNonce(i);
        bloockChain.append(newBloock);
    }

    REQUIRE(bookchain::verifyChain(bloockChain) == true);
}

TEST_CASE("verifyChain returns false if chain has block with invalid hash", "[chain][verifyChain]") {
    bookchain::Bloock genesisBlock("G E N E S I S", "B L O C K", 0);

    bookchain::Bloockchain bloockChain;
    bloockChain.purge();
    bloockChain.append(genesisBlock);

    constexpr int testBloockChainLength = 100;
    constexpr int badBlockIndex = testBloockChainLength / 2;

    for (int i = 1; i < testBloockChainLength; ++i) {
        bookchain::Bloock newBloock;
        if (i == badBlockIndex) {
            newBloock = bookchain::Bloock("B A D H A S H", "B L O C K", i);
        } else {
            newBloock = bookchain::Bloock(bloockChain.latest().blockHash(), "B L O C K", i);
        }
        newBloock.setNonce(i);
        bloockChain.append(newBloock);
    }

    REQUIRE(bookchain::verifyChain(bloockChain) == false);
}

TEST_CASE("verifyChain returns false if chain has block with invalid height", "[chain][verifyChain]") {
    bookchain::Bloock genesisBlock("G E N E S I S", "B L O C K", 0);

    bookchain::Bloockchain bloockChain;
    bloockChain.purge();
    bloockChain.append(genesisBlock);

    constexpr int testBloockChainLength = 100;
    constexpr int badBlockIndex = testBloockChainLength / 2;

    for (int i = 1; i < testBloockChainLength; ++i) {
        bookchain::Bloock newBloock;
        if (i == badBlockIndex) {
            newBloock = bookchain::Bloock(bloockChain.latest().blockHash(), "B L O C K", i + 1);
        } else {
            newBloock = bookchain::Bloock(bloockChain.latest().blockHash(), "B L O C K", i);
        }
        newBloock.setNonce(i);
        bloockChain.append(newBloock);
    }

    REQUIRE(bookchain::verifyChain(bloockChain) == false);
}
