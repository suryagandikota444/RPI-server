import serial
import time
import threading
import firebase_admin
from firebase_admin import credentials, firestore

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

time.sleep(1)
def write_read(x):
    arduino.write(bytes("{}".format(x), "UTF-8"))
    data = arduino.readline()
    return data
i = 0

while(1):
     write_read((i%2)+1)
     time.sleep(5)
     print(i)
     i += 1