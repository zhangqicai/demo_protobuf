#! /usr/bin/python3

import demo_pb2 as pb2
import socket
import time

def show_info(people):
    for person in people:
        print("id: ", person.id)
        print("name: ", person.name)
        print("email: ", person.email)
        for phone_number in person.phones:
            if phone_number.type == pb2.Person.MOBILE:
                print(" Mobile phone: ", end=" ")
            if phone_number.type == pb2.Person.HOME:
                print(" Home phone: ", end=" ")
            if phone_number.type == pb2.Person.WORK:
                print(" Work phone: ", end=" ")
            print(phone_number.number)


if __name__ == "__main__":
    demo_info = pb2.demo_info()
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    client.bind(('', 9999))

    cnt = 0
    while True:
        recv_data = client.recv(1024)
        demo_info.ParseFromString(recv_data)
        print("unparse data :",recv_data)
        show_info(demo_info.people)
        time.sleep(1)
        cnt += 1
        if cnt > 10:
            break
