import serial
import time

arduino = serial.Serial('COM11',9600)
while True:
    time.sleep(2)
    data = arduino.readline()
    print(data)
arduino.close()