from os import path
from block import Bloock

STORAGE_FILE = "theblock.chain"


def checkChain(fileName=STORAGE_FILE) -> bool:
    return path.exists(fileName)


def storeBlock(blockdata: str, fileName=STORAGE_FILE) -> None:
    with open(fileName, "a") as blockfile:
        blockfile.write(blockdata + "\n")


def storeChain(chain: list, fileName=STORAGE_FILE) -> None:
    with open(fileName, "w") as blockfile:
        for block in chain:
            blockfile.write(block + "\n")


def readChain(fileName=STORAGE_FILE):
    with open(fileName, "r") as blockfile:
        for line in blockfile:
            yield line.strip()


def getBlockById(blockId: int) -> Bloock:
    count = 0
    with open(STORAGE_FILE, "r") as blockfile:
        for line in blockfile:
            count += 1
            if count == blockId:
                blockInQuestion = Bloock()
                blockInQuestion.deserialize(line.strip())
                return blockInQuestion
    return None


def getLatestBlock() -> Bloock:
    s = ""
    with open(STORAGE_FILE, "r") as blockfile:
        for line in blockfile:
            s = line
    if s:
        b = Bloock()
        b.deserialize(s)
        return b
    else:
        return None
