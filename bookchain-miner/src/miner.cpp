#include "block.hpp"
#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Creating new bloock" << std::endl;

    Bloock testBloock("i", "i", 12);
    std::cout << testBloock.blockHash() << std::endl;
    std::cout << testBloock.blockHash() << std::endl;
}
