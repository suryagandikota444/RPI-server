import serial
import time
import threading
import firebase_admin
from firebase_admin import credentials, firestore
import numpy as np
import os
from mfrc522 import SimpleMFRC522

arduino = 1 #serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

cred = credentials.Certificate("csce483-capstone-firebase-adminsdk-oef2p-34a354f736.json")
firebase_admin.initialize_app(cred)

db = firestore.client()
callback_done = threading.Event()
rfid = SimpleMFRC522()
queue_count = 0

def write_read(x):
    # arduino.write(x)
    data = 1 #arduino.readline()
    return data

def process_request(position):
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
    else:
        print("Bin: '{}' does not exist!".format(position))

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

def on_queue_snapshot(doc_snap, changes, read_time):
    arr = []
    if len(doc_snap) > 0:
        curr_request = doc_snap[0].to_dict()
        curr_request["id"] = doc_snap[0].id
        is_alexa = curr_request["is_alexa"] 
        hist_ref = db.collection(u"History").document(u'{}'.format(curr_request["history_id"]))
        hist_doc = hist_ref.get()
        if hist_doc.exists:
            hist_doc_dict = hist_doc.to_dict()
            items_ref = db.collection(u"Items").document(u'{}'.format(hist_doc_dict["item_id"]))
            items_doc = items_ref.get()
            if items_doc.exists:
                if not is_alexa:
                    ### RFID Verification ###
                    id = ''
                    while True:
                        print("Please use rfid tag")
                        id, text = rfid.read()
                        # id = input("Please enter rfid tag: ")
                        break
                    user_docs = db.collection(u'Users').stream()
                    for user in user_docs:
                        user_dict = user.to_dict()
                        if user_dict["rfid_tag"] == id:
                            print("user found")
                            hist_ref.set({
                                u'user_id': user.id
                            }, merge=True)
                        else:
                            print("Please register RFID tag to user!")
                    process_request(items_doc.to_dict()["bin_id"])
                    print(curr_request["id"])
                    db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete()
                else:
                    process_request(items_doc.to_dict()["bin_id"])
                    print(curr_request)
                    db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete()
            else:
                print(u'item_id: {} does not exist!'.format(hist_doc_dict["item_id"]))
        else:
            print(u'history_id: {} does not exist!'.format(curr_request["history_id"]))
    else:
        print("No requests!")

test_ref = db.collection(u"test").document(u"editTest")
queue_ref = db.collection(u"Requests")

watch_bin = test_ref.on_snapshot(on_test_snapshot)
queue_watch = queue_ref.on_snapshot(on_queue_snapshot)

while True:
    time.sleep(0.5)
    # print()