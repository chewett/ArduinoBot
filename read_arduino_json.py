import serial
import time
import json

arduino = serial.Serial('COM4', 115200, timeout=None)


print "start"
time.sleep(1)
print "start"
while True:
    time.sleep(1)
    data = arduino.readline()
    if data:
        json_data = json.loads(data)
        print json_data

    time.sleep(1)
