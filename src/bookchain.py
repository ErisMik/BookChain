import copy

from block import Bloock, BloockWrapper
from storage import storeBlock, readChain

BLOCKCHAIN = []

def test():
    genBlock = BloockWrapper()
    genBlock.prevHash = 0
    genBlock.data = "Test data please ignore"
    BLOCKCHAIN.append(genBlock)

    while True:
        BLOCKCHAIN.append(fakeMine())

        for block in BLOCKCHAIN:
            print((block.prevHash, block.getHash()))

        if len(BLOCKCHAIN) > 10:
            break

    for block in BLOCKCHAIN:
        storeBlock(block.serialize())


def fakeMine():
    newBlock = BloockWrapper()
    newBlock.prevHash = BLOCKCHAIN[-1].getHash()
    newBlock.data = "My data"
    starts_right = False

    val = 0

    while not starts_right:
        print(newBlock.nonce, newBlock.getHash())
        if newBlock.getHash()[-1] == '0':
            starts_right = True
        else:
            newBlock.updateNonce(val)
        val += 1

    return newBlock

def verifyChain():
    prevBlock = None
    currBlock = None

    for line in readChain():
        currBlock = BloockWrapper()
        currBlock.deserialize(line)

        if prevBlock:
            print(prevBlock.getHash(), currBlock.prevHash)

            if prevBlock.getHash() == currBlock.prevHash:
                print("Good :)")
            else:
                print("BAD!")

        prevBlock = currBlock

if __name__ == "__main__":
    test()
    verifyChain()
