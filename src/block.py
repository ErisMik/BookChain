import json

class Bloock:
    def __init__(self, data: bytearray):
        self.data: bytearray = data
        self.hash: str = f"{hash(data)}"

class BloockWrapper:
    def __init__(self) -> None:
        self.prevHash: str = ""
        self.nonce: int = 0
        self.data: str = ""

        self.updateBloock()

    def updateBloock(self) -> None:
        self.bloock: Bloock = Bloock(self.genBloockData())

    def genBloockData(self) -> bytearray:
        dataString: str = f"{self.prevHash}{self.nonce}{self.data}"
        data: bytearray = dataString.encode("utf8")
        return data

    def updateNonce(self, newNonce: int) -> None:
        self.nonce = newNonce
        self.updateBloock()

    def getHash(self) -> str:
        return self.bloock.hash

    def serialize(self) -> str:
        payload = {
            "prev_hash": self.prevHash,
            "nonce": self.nonce,
            "data": self.data,
        }
        return json.dumps(payload)

    def deserialize(self, serializedData: str) -> None:
        payload = json.loads(serializedData)

        self.prevHash = payload["prev_hash"]
        self.nonce = payload["nonce"]
        self.data = payload["data"]
