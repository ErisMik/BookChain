#include <catch.hpp>

#include "block.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "storage.hpp"
#include "utils.hpp"

TEST_CASE("Two chain instances with the same chainID should have the same data", "[chain]") {
    bookchain::Bloock genesisBlock("GENESIS", "BLOCK", 0);

    bookchain::Bloockchain bloockchain;
    bloockchain.purge();
    bloockchain.append(genesisBlock);

    constexpr int testBloockchainLength = 100;
    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "SEED", i);
        newBloock.setNonce(i);
        bloockchain.append(newBloock);
    }

    bookchain::Bloockchain bloockchain2;

    for (int i = 1; i <= testBloockchainLength; ++i) {
        REQUIRE(bloockchain.bloock(i).blockHash() == bloockchain2.bloock(i).blockHash());
    }
}

TEST_CASE("Two chain instances with different chainIDs should NOT have the same data", "[chain]") {
    bookchain::Bloock genesisBlock("GENESIS", "BLOCK", 0);

    bookchain::Bloockchain bloockchain;
    bookchain::Bloockchain bloockchain2("AnotherChain");

    bloockchain2.purge();
    bloockchain.purge();
    bloockchain2.append(genesisBlock);
    bloockchain.append(genesisBlock);

    constexpr int testBloockchainLength = 100;
    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "SEED", i);
        newBloock.setNonce(i);
        bloockchain.append(newBloock);
    }

    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "THIS AINT THE SAME SEED", i);
        newBloock.setNonce(i);
        bloockchain2.append(newBloock);
    }

    for (int i = 1; i <= testBloockchainLength; ++i) {
        REQUIRE(bloockchain.bloock(i).blockHash() != bloockchain2.bloock(i).blockHash());
    }
}

TEST_CASE("Chain should use underlying storage to store block", "[smoke]") {
    bookchain::Bloock genesisBlock("GENESIS", "BLOCK", 0);

    bookchain::Bloockchain bloockchain;
    bloockchain.purge();
    bloockchain.append(genesisBlock);

    constexpr int testBloockchainLength = 100;
    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "SEED", i);
        newBloock.setNonce(i);
        bloockchain.append(newBloock);
    }

    constexpr unsigned int testBlockHeight = 5U;
    bookchain::Bloock fifthBlock = bookchain::storage::getBlockByHeight(testBlockHeight, &bookchain::bloockchainFilename[0]);
    REQUIRE(fifthBlock.blockHash() == bloockchain.bloock(testBlockHeight).blockHash());
}
