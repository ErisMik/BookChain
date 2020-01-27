#include "catch.hpp"

#include "block.hpp"

TEST_CASE("Blocks are zeroed out when constructed", "[block]") {
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

TEST_CASE("Blocks have the same hash after copy", "[block]") {
    constexpr int fakeHeight = 66;

    bookchain::Bloock bloock1("foobarfakehash", "foobarfakehash", fakeHeight);
    bookchain::Bloock bloock2(bloock1);
    bookchain::Bloock bloock3 = bloock1;

    REQUIRE(bloock1.blockHash() == bloock2.blockHash());
    REQUIRE(bloock1.blockHash() == bloock3.blockHash());
}