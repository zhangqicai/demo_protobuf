#! /usr/bin/python3

import demo_pb2 as pb2
import sys
import socket
import time


if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    while True:
        print("server is running")
        buf = "test"
        sock.sendto(buf.encode(), ('255.255.255.255',9999))
        time.sleep(1)
