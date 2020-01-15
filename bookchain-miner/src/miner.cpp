#include "block.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Creating new bloock" << std::endl;

    Bloock testBloock("i", "i", 12);
    testBloock.writeData("i");
    std::cout << utils::hexifystring(testBloock.blockHash()) << std::endl;

    Bloock testBloockTwo(testBloock.block());
    std::cout << utils::hexifystring(testBloockTwo.blockHash()) << std::endl;
}
