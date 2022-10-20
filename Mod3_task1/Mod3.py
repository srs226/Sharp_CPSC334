#import libraries
import socket
import argparse
from pythonosc import udp_client

#set host, port, and data buffer size - set up socket
HOST = "172.29.21.213"

PORT = 8092

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind((HOST, PORT))

#checks
parser = argparse.ArgumentParser()
parser.add_argument("--ip", default=HOST,
help="The ip of the OSC server")
parser.add_argument("--port", type=int, default=12000,
help="The port the OSC server is listening on")
args = parser.parse_args()

client = udp_client.SimpleUDPClient(args.ip, args.port)

#print data to terminal and send it to processing
while True:
        data, addy = s.recvfrom(BUFFER_SIZE)
        if data:
                print("Client to server: ", data.decode("ASCII"))
                client.send_message("me", data.decode("ASCII"))
