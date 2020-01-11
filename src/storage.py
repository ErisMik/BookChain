STORAGE_FILE = "theblock.chain"

def storeBlock(blockdata: str) -> None:
    with open(STORAGE_FILE, "a") as blockfile:
        blockfile.write(blockdata + "\n")

def readChain():
    with open(STORAGE_FILE, "r") as blockfile:
        for line in blockfile:
            yield line.strip()
