import json
import lzma
import requests
from flask import Flask, jsonify, request
from flask_cors import CORS

from multiprocessing import Process, Pipe, Queue, Array
from ctypes import c_int32
from netaddr import IPNetwork, IPAddress

from storage import readChain, getBlockById, getLatestBlock
from miner import mine, premine

LINK_CODE = 'Bookchain Linky'

app = Flask(__name__)
CORS(app)

PEERS = Queue()
PENDING_BOOKS = Queue()
NETWORK_DIFFICULTY = 14


@app.route('/', methods=['GET'])
def pong():
    print(request.host)
    return LINK_CODE + " " + str(hash(LINK_CODE))


@app.route('/find-peers', methods=['GET'])
def find_peers():
    all_ips = list(IPNetwork("172.20.10.0/24"))
    for ip in all_ips:
        try:
            print(f"Trying: {str(ip)}")
            r = requests.get(f"http://{str(ip)}:5000/", timeout=0.5)
            print(r.text)

            if LINK_CODE in r.text and str(hash(LINK_CODE)) not in r.text:
                print("Found peer!")
                PEERS.put(int(ip))
        except:
            pass

    return jsonify({'success': True})


@app.route('/blocks', methods=['GET'])
def blocks():
    blockchain = []
    for block in readChain():
        blockchain.append(block)

    return jsonify(blockchain)

@app.route('/blocks-from/<int:blockId>', methods=['GET'])
def blocksFrom(blockId):
    blockchainSlice = []
    count = 0
    for block in readChain():
        count += 1
        if count < blockId:
            continue
        blockchainSlice.append(block)

    return jsonify(blockchainSlice)

def compressText(text: str) -> str:
    rawEncodedText = text.encode('utf-8')
    compressedEncodedText = lzma.compress(rawEncodedText)

    print("Compression ratio:", len(rawEncodedText) / len(compressedEncodedText))

    return compressedEncodedText.hex()


def uncompressText(compressedHexText: str) -> str:
    compressedEncodedText = bytes.fromhex(compressedHexText)
    rawEncodedText = lzma.decompress(compressedEncodedText)
    return rawEncodedText.decode('utf-8')


@app.route('/create-book', methods=['POST'])
def createBook():
    requestData = request.json

    for requiredTag in ['meta', 'text']:
        if requiredTag not in requestData:
            return abort(400, f"Missing tag {requiredTag}")

    if not isinstance(requestData['text'], str):
        return abort(400, "Text data is not text data!")

    payload = {
        'meta': requestData['meta'],
        'text': compressText(requestData['text']),
    }

    PENDING_BOOKS.put(json.dumps(payload))

    return jsonify({'success': True})


@app.route('/get-book/<int:blockId>', methods=['GET'])
def getBook(blockId: int):
    result = getBlockById(blockId)
    if not result:
        abort(404, "Could not find that record")

    book = json.loads(result.data)

    payload = {
        'meta': book['meta'],
        'text': uncompressText(book['text']),
    }

    return jsonify(payload)


@app.route('/get-block/<int:blockId>', methods=['GET'])
def getBlock(blockId: int):
    result = getBlockById(blockId)
    if not result:
        abort(404, "Could not find that record")

    payload = {
        'hash': result.hash,
        'data': result.data,
        'nonce': result.nonce,
        'height': result.height,
        'prevhash': result.prevHash,
        'seedhash': result.seedHash
    }
    return jsonify(payload)


if __name__ == '__main__':
    print("======================")
    print("Bookchain starting up!")
    print("======================")

    # Start mining
    premine()
    a, b = Pipe()
    p1 = Process(target=mine, args=(
        a, PENDING_BOOKS, NETWORK_DIFFICULTY, PEERS))
    p1.start()

    # Start server to receive transactions
    p2 = Process(target=app.run(host="0.0.0.0", port="5000"), args=(b,))
    p2.start()
