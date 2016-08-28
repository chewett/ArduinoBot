import serial
import socket
import json
import time


arduino = serial.Serial('COM4', 115200, timeout=None)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 31415)
sock.connect(server_address)

sock.sendall('{"mode": "sender"}\n')

print "starting"
while True:
    data = arduino.readline()
    if data:
        json_data = json.loads(data)
        print json_data
        sock.sendall(data)


