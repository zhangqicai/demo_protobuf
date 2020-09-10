#! /usr/bin/python3

import demo_pb2 as pb2
import socket
import time

if __name__ == "__main__":
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    client.bind(('', 9999))

    cnt = 0
    while True:
        recv_data = client.recv(1024)
        print(recv_data)
        time.sleep(1)
        cnt += 1
        if cnt > 10:
            break
