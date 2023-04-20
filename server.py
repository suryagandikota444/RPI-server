import serial
import time
import threading
import firebase_admin
from firebase_admin import credentials, firestore
import numpy as np
import os
from mfrc522 import SimpleMFRC522
from flask import Flask, render_template
#import serial
import threading
import queue
from flask import Flask, render_template, redirect, url_for
#import serial
import threading
import queue
from flask import jsonify
import ast
import RPi.GPIO as GPIO




#global running
#running = False


arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
print(arduino)

cred = credentials.Certificate("/home/pi/Documents/AS/csce483-capstone-firebase-adminsdk-oef2p-34a354f736.json")
firebase_admin.initialize_app(cred)

db = firestore.client()
callback_done = threading.Event()
rfid = SimpleMFRC522()
GPIO.cleanup()
queue_count = 0
semaphore = threading.Semaphore(1)

def write_read(x, request_id):
    arduino.write(x)
    data = arduino.readline()
    #time.sleep(2.5) #SHHHHHHhshhhhh
    # semaphore.acquire()
    dataVal = ""
    with open('/home/pi/Documents/AS/data.txt', 'r') as file:
        dataVal = file.read().strip()
        if dataVal == "False":
            dataVal = False
        elif dataVal == "True":
            dataVal = True

    while dataVal:
        with open('/home/pi/Documents/AS/data.txt', 'r') as file:
            dataVal = file.read().strip()
            if dataVal == "False":
                dataVal = False
            elif dataVal == "True":
                dataVal = True
    # semaphore.release()
    db.collection(u'Requests').document(u'{}'.format(request_id)).delete()
    print('success') 
    time.sleep(2)
    return data

def process_request(position, request_id):
    #global running
    #running = True
    if position == "A0":
        print(f"A0")
        write_read(b'A0', request_id)
    elif position == "A1":
        print(f"A1")
        write_read(b'A1', request_id)
    elif position == "A2":
        print(f"A2")
        write_read(b'A2', request_id)
    elif position == "A3":
        print(f"A3")
        write_read(b'A3', request_id)
    elif position == "A0":
        print(f"A0")
        write_read(b'B0', request_id)
    elif position == "B1":
        print(f"B1")
        write_read(b'B1', request_id)
    elif position == "B2":
        print(f"B2")
        write_read(b'B2', request_id)
    elif position == "B3":
        print(f"B3")
        write_read(b'B3', request_id)
    elif position == "C0":
        print(f"C0")
        write_read(b'C0', request_id)
    elif position == "C1":
        print(f"C1")
        write_read(b'C1', request_id)
    elif position == "C2":
        print(f"C2")
        write_read(b'C2', request_id)
    elif position == "C3":
        print(f"C3")
        write_read(b'C3', request_id)
    elif position == "C4":
        print(f"C4")
        write_read(b'C4', request_id)
    elif position == "C5":
        print(f"C5")
        write_read(b'C5', request_id)
    elif position == "C6":
        print(f"C6")
        write_read(b'C6', request_id)
    elif position == "C7":
        print(f"C7")
        write_read(b'C7', request_id)
    else:
        print("Bin: '{}' does not exist!".format(position))
    
    



def on_queue_snapshot(doc_snap, changes, read_time):
    #global running
    #running = True
    GPIO.cleanup()
    arr = []
    print("running")
    #enter the loop only if there are any items in collection on change
    change = ""
    if len(doc_snap) > 1:
        doc_snap = [doc_snap[-1]] 
        change = changes[-1].type.name
    if change == "ADDED":
        for doc in doc_snap:
            if doc.id != "0":
                with open("/home/pi/Documents/AS/data.txt", "w") as f:
                    f.write("True")
                    print("True")
                curr_request = doc.to_dict() #save curr request to send right data to history record
                curr_request["id"] = doc.id 
                is_alexa = curr_request["is_alexa"] #check if alexa
                is_checkout = curr_request["is_checkout"]
                with open("data2.txt", "w") as f2:
                    f2.write(f"{is_checkout}")

                if curr_request["history_id"] == None:
                    process_request(curr_request["bin_id"], curr_request["id"])
                else:
                    # route for links between collection is: History -> Items -> Bin 
                    hist_ref = db.collection(u"History").document(u'{}'.format(curr_request["history_id"])) # first, history
                    hist_doc = hist_ref.get()
                    if hist_doc.exists:
                        hist_doc_dict = hist_doc.to_dict()
                        items_ref = db.collection(u"Items").document(u'{}'.format(hist_doc_dict["item_id"])) # second, items
                        items_doc = items_ref.get()
                        if items_doc.exists:

                            # branch for alexa because it needs rfid verification
                            if is_alexa:
                                ### RFID Verification ###
                                id = ''
                                while True:
                                    print("Please use rfid tag")
                                    id, text = rfid.read()
                                    GPIO.cleanup()
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
                                
                                # send bin to read_write function to be sent to arduino
                                process_request(items_doc.to_dict()["bin_id"], curr_request["id"])
                                # print(curr_request["id"])
                                # db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete() #delete queued item
                            else:

                                # no verification since its from phone
                                process_request(items_doc.to_dict()["bin_id"], curr_request["id"])
                                #print(curr_request)
                                # db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete()
                            
                            
                        else:
                            print(u'item_id: {} does not exist!'.format(hist_doc_dict["item_id"]))
                    else:
                        print(u'history_id: {} does not exist!'.format(curr_request["history_id"]))
                break
        else:
            print("No requests!")

def on_rfid_snapshot(doc_snap, changes, read_time):
    for doc in doc_snap:
        docDict = doc.to_dict()
        if docDict['live'] == True:
            print("Please use rfid tag")
            while True:
                id, text = rfid.read()
                print(id)
                break
            db.collection(u'Users').document(u'{}'.format(docDict["userid"])).update({ "rfid_tag": id })
            db.collection(u'RFIDinit').document(u'VTflY8VUypi61GVplO8p').update({ "live": False, "userid": "" })

GPIO.cleanup()
queue_ref = db.collection(u"Requests").order_by(u"timestamp")
rfid_ref = db.collection(u"RFIDinit").document(u"VTflY8VUypi61GVplO8p")

queue_watch = queue_ref.on_snapshot(on_queue_snapshot)
rfid_watch = rfid_ref.on_snapshot(on_rfid_snapshot)

while True:
    time.sleep(0.5)
    # print()
