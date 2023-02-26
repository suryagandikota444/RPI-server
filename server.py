import serial
import time
import threading
import firebase_admin
from firebase_admin import credentials, firestore

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

cred = credentials.Certificate("csce483-capstone-firebase-adminsdk-oef2p-34a354f736.json")
firebase_admin.initialize_app(cred)

db = firestore.client()
callback_done = threading.Event()

boolValue = False

def write_read(x):
    arduino.write(x)
    data = arduino.readline()
    return data

def on_snapshot(doc_snap, changes, read_time):
    for doc in doc_snap:
        docDict = doc.to_dict()
        isTrue = docDict["isTrue"]
        if isTrue == "1":
            print(f"Snap isTrue: {isTrue}")
            write_read(b'1')
        if isTrue == "2":
            print(f"Snap isTrue: {isTrue}")
            write_read(b'2')
        global boolValue
        boolValue = isTrue
    callback_done.set()

doc_ref = db.collection(u"test").document(u"test")

doc_watch = doc_ref.on_snapshot(on_snapshot)

while True:
    time.sleep(0.5)