import socket
import RPi.GPIO as GPIO
import time

#initialize variables for socket
HOST = "172.29.24.126"
PORT = 8092
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((HOST, PORT))

#set GPIO board and pins
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7,GPIO.IN)
prev_input = 0

#wait until the pi gets an initial message from the esp to get address
message = True
while message:
	data, addy = s.recvfrom(PORT)
	message = False
	print(addy)
#poll to detect when sensor is pressed - got code flow from: https://pimylifeup.com/raspberry-pi-pressure-pad/ -
while True:
	#take a reading
	input = GPIO.input(7)
	#if the last reading was low and this one high, alert us
	if ((not prev_input) and input):
		print("Under Pressure")
		#send an alert to the esp
		s.sendto(b'1', addy)
	#update previous input
	prev_input = input
	#slight pause
	time.sleep(0.05)
