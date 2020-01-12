import json
import hashlib

class Bloock:
    def __init__(self) -> None:
        self.prevHash: str = ""
        self.nonce: int = 0
        self.data: str = ""
        self.seedHash: str = ""
        self.hash: str = ""
        self.height: int = 0

    def serialize(self) -> str:
        payload = {
            "prev_hash": self.prevHash,
            "nonce": self.nonce,
            "data": self.data,
            "seed_hash": self.seedHash,
            "hash": self.hash,
            "height": self.height
        }
        return json.dumps(payload)

    def deserialize(self, serializedData: str) -> None:
        payload = json.loads(serializedData)

        self.prevHash = payload["prev_hash"]
        self.nonce = payload["nonce"]
        self.data = payload["data"]
        self.seedHash = payload["seed_hash"]
        self.hash = payload["hash"]
        self.height = payload["height"]
