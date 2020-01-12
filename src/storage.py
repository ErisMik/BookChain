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
