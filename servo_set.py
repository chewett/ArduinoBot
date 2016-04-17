import serial, time
arduino = serial.Serial('COM5', 9600, timeout=None)

print "start"
time.sleep(1)
print "start"
while True:
    time.sleep(1)
    print "start1"
    arduino.write("60")
    data = arduino.readline()
    if data:
        print data

    time.sleep(1)
    print "start2"
    arduino.write("120")
    data = arduino.readline()
    if data:
        print data

