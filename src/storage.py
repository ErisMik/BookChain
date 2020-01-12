from block import Bloock
STORAGE_FILE = "theblock.chain"


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


def getBlockById(blockId: int):
    count = 0
    with open(STORAGE_FILE, "r") as blockfile:
        for line in blockfile:
            count += 1
            if count == blockId:
                return line.strip()
    return None


def getLatestBlock():
    with open(STORAGE_FILE, "r") as blockfile:
        blockfile.seek(0, 2)
        s = blockfile.readline()
        b = Bloock()
        b.deserialize(s)
        return b
