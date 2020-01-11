class Bloock:
    def __init__(data: bytearray):
        self.data: bytearray = data
        self.hash: str = len(data)  # FIX-ME

class BloockWrapper:
    def __init__() -> None:
        self.prevHash: str = ""
        self.nonce: int = 0
        self.data: str = ""

        self.bloock: Bloock = Bloock(genBloockData())

    def genBloockData() -> bytearray:
        dataString: str = f"{self.prevHash}{self.nonce}{self.data}"
        data: bytearray = dataString.encode("utf8")
        return data

    def updateNonce(newNonce: int) -> None:
        self.nonce = newNonce
