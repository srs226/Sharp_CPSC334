import socket

HOST = "172.29.128.95"

PORT = 8092

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#DGRAM)

s.bind((HOST, PORT))

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(7,GPIO.IN)

prev_input = 0

message = True

#while message:
#	data, addy = s.recvfrom(8092)
#	message = False

while True:
	#take a reading
	input = GPIO.input(7)
	#if the last reading was low and this one high, alert us
	if ((not prev_input) and input):
		print("Under Pressure")
		s.sendto(b'1',(HOST, PORT))
	#update previous input
	prev_input = input
	#slight pause
	time.sleep(0.05)



button = 7
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(button,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)

def button_call(channel):
	begin = time.time()
	if begin - time.time() < .2:
		s.send(b'1')

GPIO.add_event_detect(button,GPIO.FALLING,callback=button_call,bouncetime=100)

