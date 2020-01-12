import pyrx
import binascii
import random
import requests

from block import Bloock
from storage import storeBlock, readChain, storeChain

seed_hash = binascii.unhexlify(
    "0ea23341e489a9720ff4bfbd0391338918a295d46416b87dfe8a785cce9eb51d")


# Currently loading the entire blockchain into ram
def mine(a, bc, pendingData, networkDiff, peers):
    nextData = pendingData.pop()
    newBlock = Bloock()
    newBlock.prevHash = bc[-1].hash
    newBlock.data = nextData
    newBlock.seed_hash = seed_hash
    height = len(bc) + 1

    # Try random nonces from 1 to 2^63-1
    trialNonce = random.randint(0, 9223372036854775807)

    while True:
        print("Hashing with nonce: ", trialNonce)
        candidate = pyrx.get_rx_hash(
            newBlock.prevHash + newBlock.data + str(trialNonce), seed_hash, height)
        candidate = binascii.hexlify(candidate).decode()
        if foundBlock(candidate, networkDiff, height):
            newBlock.nonce = trialNonce
            newBlock.hash = candidate
            newBlock.height = height
            # Add to network chain and json file and start the next block
            bc.append(newBlock)
            storeBlock(newBlock.serialize())
            newBlock = Bloock()
            newBlock.prevHash = bc[-1].hash
            nextData = pendingData.pop()
            newBlock.seed_hash = seed_hash
            height = len(bc) + 1

        trialNonce = random.randint(0, 9223372036854775807)


# Difficulty is currently # of leading 0s in binary hash
def foundBlock(hash, difficulty, height):
    check = '0'*difficulty + '1'*(256-difficulty)
    check = int(check, 2)
    hash = int(hash, 16)
    # Valid block found
    if check & hash == hash and checkNetwork(height):
        return True


def verifyChain(chain):
    prevBlock = None
    currBlock = None

    for line in chain:
        currBlock = Bloock()
        currBlock.deserialize(line)

        # Run randomx to verify nonce, data, hash of block
        if prevBlock and prevBlock.hash == currBlock.prevHash:
            print(prevBlock.hash, currBlock.prevHash)
            verifyhash = pyrx.get_rx_hash(
                prevBlock.hash + currBlock.data + str(currBlock.nonce), currBlock.seedHash, currBlock.height)
            verifyhash = binascii.hexlify(verifyhash).decode()
            if verifyhash == currBlock.hash:
                print("Good :)")
            else:
                print("BAD!")
                return False
        elif not prevBlock:
            verifyhash = pyrx.get_rx_hash(
                currBlock.prevHash + currBlock.data +
                str(currBlock.nonce), currBlock.seedHash, currBlock.height
            )
            verifyhash = binascii.hexlify(verifyhash).decode()
            if verifyhash == currBlock.hash:
                print("Good genesis block :)")
            else:
                print("BAD!")
                return False
        prevBlock = currBlock
    return True


def checkNetwork(peers, height):
    behind = False
    for p in peers:
        print(f"Verifying {str(p)}'s blockchain")
        r = requests.get(f"http://{str(p)}:5000/blocks", timeout=1)
        if len(r.json) > height and verifyChain(r.json):
            behind = True
            storeChain(r.json)
            height = len(r.json)
    return not behind
