#include <catch.hpp>

#include "block.hpp"
#include "chain.hpp"
#include "chaintools.hpp"
#include "storage.hpp"
#include "utils.hpp"

TEST_CASE("Basic smoke test", "[smoke]") {
    bookchain::Bloock testBloock("i", "i", 0);
    testBloock.writeData("i");
    bookchain::Bloock testBloockTwo(testBloock.block());

    REQUIRE(testBloock.blockHash() == testBloockTwo.blockHash());
    REQUIRE(testBloock.prevHash() == testBloockTwo.prevHash());
    REQUIRE(testBloock.data() == testBloockTwo.data());

    bookchain::Bloockchain bloockchain;
    bloockchain.purge();
    bloockchain.append(testBloock);

    constexpr int testBloockchainLength = 100;
    for (int i = 1; i <= testBloockchainLength; ++i) {
        bookchain::Bloock newBloock(bloockchain.latest().blockHash(), "i", i);
        newBloock.setNonce(i);
        bloockchain.append(newBloock);
    }

    REQUIRE(bookchain::verifyChain(bloockchain) == true);
    REQUIRE(bloockchain.height() == testBloockchainLength);

    bookchain::Bloockchain bloockchain2;

    REQUIRE(bookchain::verifyChain(bloockchain2) == true);
    REQUIRE(bloockchain.height() == bloockchain2.height());

    constexpr unsigned int testBlockHeight = 5U;
    bookchain::Bloock fifthBlock = bookchain::storage::getBlockByHeight(testBlockHeight, &bookchain::bloockchainFilename[0]);
    REQUIRE(fifthBlock.blockHash() == bloockchain.bloock(testBlockHeight).blockHash());
}
