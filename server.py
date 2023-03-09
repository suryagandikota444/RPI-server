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

def write_read(x):
    arduino.write(x)
    data = arduino.readline()
    return data

def on_test_snapshot(doc_snap, changes, read_time):
    for doc in doc_snap:
        docDict = doc.to_dict()
        position = docDict["position"]
        if position == "A0":
            print(f"A0")
            write_read(b'A0')
        elif position == "A1":
            print(f"A1")
            write_read(b'A1')
        elif position == "A2":
            print(f"A2")
            write_read(b'A2')
        elif position == "A3":
            print(f"A3")
            write_read(b'A3')
        elif position == "A0":
            print(f"A0")
            write_read(b'B0')
        elif position == "B1":
            print(f"B1")
            write_read(b'B1')
        elif position == "B2":
            print(f"B2")
            write_read(b'B2')
        elif position == "B3":
            print(f"B3")
            write_read(b'B3')
        elif position == "C0":
            print(f"C0")
            write_read(b'C0')
        elif position == "C1":
            print(f"C1")
            write_read(b'C1')
        elif position == "C2":
            print(f"C2")
            write_read(b'C2')
        elif position == "C3":
            print(f"C3")
            write_read(b'C3')
        elif position == "C4":
            print(f"C4")
            write_read(b'C4')
        elif position == "C5":
            print(f"C5")
            write_read(b'C5')
        elif position == "C6":
            print(f"C6")
            write_read(b'C6')
        elif position == "C7":
            print(f"C7")
            write_read(b'C7')
    callback_done.set()

# def on_queue_snapshot(doc_snap, changes, read_time):
#     print(changes)
#     for doc in doc_snap:
#         print(doc)

test_ref = db.collection(u"test").document(u"editTest")
# queue_ref = db.collection(u"Requests")

watch_bin = test_ref.on_snapshot(on_test_snapshot)
# queue_watch = queue_ref.on_snapshot(on_queue_snapshot)

while True:
    time.sleep(0.5)
    # print(dir(queue_ref.list_documents))
    # print()