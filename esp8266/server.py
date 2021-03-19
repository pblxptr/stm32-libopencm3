#!/usr/bin/env python

import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_address = ('192.168.0.115', 5566)
ip, port = server_address
print("Starting up on {0} port {1}.".format(ip, port))

sock.bind(server_address)

sock.listen(1)

def receive(s, size):
  print("Waiting for data...")

  received = str(s.recv(size), "utf-8")

  s.sendall(bytes("bbbb" + "\n", "utf-8"))
  
  print("Received: {}".format(received))

while True:
    # Wait for a connection
    print("Waiting for connection.")
    connection, client_address = sock.accept()
    print("Connected")

    receive(connection, 4)