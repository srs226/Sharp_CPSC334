import socket

HOST = "172.29.24.126"

PORT = 8092

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind((HOST, PORT))
while True:
	data, addy = s.recvfrom(BUFFER_SIZE)
	if data:
		print("Client to server: ", data.decode("ASCII"))
s.close()
