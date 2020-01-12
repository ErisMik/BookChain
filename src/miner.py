import pyrx
import binascii
import random
import requests
import json

from block import Bloock
from storage import storeBlock, readChain, storeChain, getLatestBlock, checkChain

seed_hash = binascii.unhexlify(
    "0ea23341e489a9720ff4bfbd0391338918a295d46416b87dfe8a785cce9eb51d")


def premine():
    if checkChain():
        print("Reusing existing chain")
    else:
        print("Creating the genesis block")
        genBlock = Bloock()
        genBlock.data = json.dumps({"meta": {}, "text": "G E N E S I S"})
        genBlock.height = 1
        genBlock.nonce = 0
        genBlock.seed_hash = seed_hash

        hash = pyrx.get_rx_hash(genBlock.prevHash + genBlock.data + str(genBlock.nonce), seed_hash, 1)
        genBlock.hash = binascii.hexlify(hash).decode()

        storeBlock(genBlock.serialize())


# Currently loading the entire blockchain into ram
def mine(a, pendingData, networkDiff, peers):
    latestBlock = getLatestBlock()
    nextData = json.dumps(dict())
    if not pendingData.empty():
        nextData = pendingData.get()
    newBlock = Bloock()
    newBlock.prevHash = latestBlock.hash
    newBlock.data = nextData
    newBlock.seed_hash = seed_hash
    height = latestBlock.height + 1

    # Try random nonces from 1 to 2^63-1
    trialNonce = random.randint(0, 9223372036854775807)

    while True:
        print("Hashing with nonce: ", trialNonce)
        candidate = pyrx.get_rx_hash(
            newBlock.prevHash + newBlock.data + str(trialNonce), seed_hash, height)
        candidate = binascii.hexlify(candidate).decode()
        if foundBlock(candidate, networkDiff, height, peers):
            newBlock.nonce = trialNonce
            newBlock.hash = candidate
            newBlock.height = height
            # Add to network chain and json file and start the next block
            storeBlock(newBlock.serialize())
            latestBlock = newBlock
            newBlock = Bloock()
            newBlock.prevHash = latestBlock.hash
            newBlock.seed_hash = seed_hash
            nextData = json.dumps(dict())
            if not pendingData.empty():
                nextData = pendingData.get()
            height += 1
        else:
            latestBlock = getLatestBlock()
            newBlock.prevHash = latestBlock.hash

        trialNonce = random.randint(0, 9223372036854775807)


# Difficulty is currently # of leading 0s in binary hash
def foundBlock(hash, difficulty, height, peers):
    check = '0'*difficulty + '1'*(256-difficulty)
    check = int(check, 2)
    hash = int(hash, 16)
    # Valid block found
    if check & hash == hash and checkNetwork(peers, height):
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
        if len(r.json) >= height and verifyChain(r.json):
            behind = True
            storeChain(r.json)
            height = len(r.json)
    return not behind
