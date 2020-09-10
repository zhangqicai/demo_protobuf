#! /usr/bin/python3

import demo_pb2 as pb2
import sys
import socket
import time


def gen_person_info(people:list, person_id:int, name='test', email="test@viz.com"):
    person = pb2.Person()
    person.id = person_id
    person.name = name
    person.email = email

    phone_number = person.phones.add()
    phone_number.number = "2222800"
    phone_number.type = pb2.Person.WORK

    people.append(person)


if __name__ == '__main__':
    demo_info =  pb2.demo_info()
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    
    count = 0
    while True:
        print("server is running ", count)
        _id = count
        _name = f"zh{count}"
        _email = f"{count}@viz.com" 
        demo_info.Clear()
        gen_person_info(demo_info.people, _id, _name, _email)
        buf = demo_info.SerializeToString()
        sock.sendto(buf, ('255.255.255.255',9999))
        time.sleep(1)
        count += 1
