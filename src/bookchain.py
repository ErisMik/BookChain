import copy
import pyrx
import binascii
import random

from block import Bloock
from storage import storeBlock, readChain


BLOCKCHAIN = []
# TODO: Get these params from network consensus
seed_hash = binascii.unhexlify("0ea23341e489a9720ff4bfbd0391338918a295d46416b87dfe8a785cce9eb51d")
difficulty = 2


def test():
    genBlock = Bloock()
    genBlock.prevHash = "0"
    genBlock.data = "G E N I S I S"
    genBlock.nonce = 1
    genBlock.height = 1
    genBlock.seed_hash = seed_hash
    hash = pyrx.get_rx_hash(genBlock.prevHash + genBlock.data + str(genBlock.nonce), seed_hash, 1)
    genBlock.hash = binascii.hexlify(hash).decode()
    BLOCKCHAIN.append(genBlock) 
    
    while True:
        BLOCKCHAIN.append(fakeMine(difficulty))

        for block in BLOCKCHAIN:
            print((block.prevHash, block.hash))

        if len(BLOCKCHAIN) > 10:
            break

    for block in BLOCKCHAIN:
        storeBlock(block.serialize())


def fakeMine(difficulty):
    newBlock = Bloock()
    newBlock.prevHash = BLOCKCHAIN[-1].hash
    newBlock.data = "My data"
    newBlock.seed_hash = seed_hash
    height = len(BLOCKCHAIN) + 1
    
    #Try random nonces from 1 to 2^63-1
    trialNonce = random.randint(0,9223372036854775807)

    while True:
        print("Hashing with nonce: ", trialNonce)
        candidate = pyrx.get_rx_hash(newBlock.prevHash + newBlock.data + str(trialNonce), seed_hash, height)
        candidate = binascii.hexlify(candidate).decode()
        if foundBlock(candidate, difficulty):
            newBlock.nonce = trialNonce
            newBlock.hash = candidate
            newBlock.height = height
            break
        else:
            trialNonce = random.randint(0,9223372036854775807)

    return newBlock

# Difficulty is currently # of leading 0s in binary hash
def foundBlock(hash, difficulty):
    check = '0'*difficulty + '1'*(256-difficulty)
    check = int(check, 2)
    hash = int(hash, 16)
    #Valid block found
    if check & hash == hash:
        return True
    
def verifyChain():
    prevBlock = None
    currBlock = None

    for line in readChain():
        currBlock = Bloock()
        currBlock.deserialize(line)

        #Run randomx to verify nonce, data, hash of block
        if prevBlock and prevBlock.hash == currBlock.prevHash:
            print(prevBlock.hash, currBlock.prevHash)
            verifyhash = pyrx.get_rx_hash(prevBlock.hash + currBlock.data + str(currBlock.nonce), currBlock.seedHash, currBlock.height)
            verifyhash = binascii.hexlify(verifyhash).decode()
            if verifyhash == currBlock.hash:
                print("Good :)")
            else:
                print("BAD!")

        prevBlock = currBlock

if __name__ == "__main__":
    test()
    verifyChain()
