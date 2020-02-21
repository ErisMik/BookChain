#include <catch.hpp>

#include "block.hpp"

TEST_CASE("Blocks should be zeroed out when constructed", "[block]") {
    bookchain::Bloock bloock;
    bookchain::Block block = bloock.block();

    char* blockBytes = reinterpret_cast<char*>(&block);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    char result = '\0';
    for (size_t i = 0; i < sizeof(block); ++i) {
        char blockByte = blockBytes[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (blockByte != '\0') {
            result = blockByte;
        }
    }

    REQUIRE(result == '\0');
}

TEST_CASE("Blocks should have the same hash after copy", "[block]") {
    constexpr int fakeHeight = 66;

    bookchain::Bloock bloock1("foobarfakehash", "foobarfakehash", fakeHeight);
    bookchain::Bloock bloock2(bloock1);
    bookchain::Bloock bloock3 = bloock1;

    REQUIRE(bloock1.blockHash() == bloock2.blockHash());
    REQUIRE(bloock1.blockHash() == bloock3.blockHash());
}

TEST_CASE("Block data with null bytes should still return the full data", "[block]") {
    constexpr int fakeHeight = 66;

    bookchain::Bloock bloock("foobarfakehash", "foobarfakehash", fakeHeight);
    std::string dataWithNullBytes("prenull");
    dataWithNullBytes += '\0';
    dataWithNullBytes += "postnull";
    bloock.writeData(dataWithNullBytes);

    REQUIRE(bookchain::blockDataLength == bloock.data().size());
}
