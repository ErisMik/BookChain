import requests
from flask import Flask, jsonify
from multiprocessing import Process, Pipe
from netaddr import IPNetwork, IPAddress

from storage import readChain

LINK_CODE = 'Bookchain Linky'

app = Flask(__name__)
peers = []
networkDiff = 12


@app.route('/')
def pong():
    return LINK_CODE


@app.route('/findpeers', methods=['GET'])
def find_peers():
    all_ips = list(IPNetwork("192.168.0.0/24"))
    for ip in all_ips:
        try:
            print(f"Trying: {str(ip)}")
            r = requests.get(f"http://{str(ip)}:5000/", timeout=1)

            if LINK_CODE in r.text:
                peers.append(str(ip))
        except:
            pass


@app.route('/blocks', methods=['GET'])
def blocks():
    blockchain = []
    for block in readChain():
        blockchain.append(block)

    return jsonify(blockchain)


if __name__ == '__main__':
    print("======================")
    print("Bookchain starting up!")
    print("======================")

    # Start mining
    a, b = Pipe()
    # p1 = Process(target=mine, args=(a, BLOCKCHAIN, NODE_PENDING_TRANSACTIONS, networkDiff, peers))
    # p1.start()

    # Start server to receive transactions
    p2 = Process(target=app.run(host="0.0.0.0", port="5000"), args=b)
    p2.start()
