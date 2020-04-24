from __future__ import print_function

import sys
import time
import zmq
import numpy
import json
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--type', dest='stype', type=str, default='SUB')
parser.add_argument('--host', dest='host', type=str, default='tcp://127.0.0.1:1234')

args = parser.parse_args()
if args.stype == 'SUB' or args.stype == 'PUB':
    stype = zmq.SUB
elif args.stype == 'PULL' or args.stype == 'PUSH':
    stype = zmq.PULL
else:
    stype = zmq.SUB
    print("Unsupported socket type %s, use SUB"%args.stype)


context = zmq.Context()
sock = context.socket(stype)
if stype == zmq.SUB:
    sock.setsockopt(zmq.SUBSCRIBE, b'')
    sock.connect(args.host)
elif stype == zmq.PULL:
    sock.bind(args.host)

print('Client %s %s'%(args.host,args.stype))

while True:
    # receive header
    try:
        header = sock.recv()
        if sys.hexversion >= 0x03000000:
            header = header.decode()
    except:
        break
    print(header)
    info = json.loads(header)

    # receive data
    data = numpy.frombuffer(sock.recv(), dtype=str(info['type']))
    data.reshape(info['shape'])
    print(data.sum(),data)
