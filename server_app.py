import serial
import time
import threading
import firebase_admin
from firebase_admin import credentials, firestore
import numpy as np
import os
from mfrc522 import SimpleMFRC522
from flask import Flask, render_template
import serial
import threading
import queue
from flask import Flask, render_template, redirect, url_for
import serial
import threading
import queue
import ast
from flask import jsonify


# arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

# cred = credentials.Certificate("csce483-capstone-firebase-adminsdk-oef2p-34a354f736.json")
# firebase_admin.initialize_app(cred)

# db = firestore.client()
# callback_done = threading.Event()
# rfid = SimpleMFRC522()
# queue_count = 0
# global running


# def write_read(x):
#     global running
#     running = True
#     arduino.write(x)
#     data = arduino.readline()
#     running = False
#     return data

# def process_request(position): 
#     global running
#     running = True   
#     if position == "A0":
#         print(f"A0")
#         write_read(b'A0')
#     elif position == "A1":
#         print(f"A1")
#         write_read(b'A1')
#     elif position == "A2":
#         print(f"A2")
#         write_read(b'A2')
#     elif position == "A3":
#         print(f"A3")
#         write_read(b'A3')
#     elif position == "A0":
#         print(f"A0")
#         write_read(b'B0')
#     elif position == "B1":
#         print(f"B1")
#         write_read(b'B1')
#     elif position == "B2":
#         print(f"B2")
#         write_read(b'B2')
#     elif position == "B3":
#         print(f"B3")
#         write_read(b'B3')
#     elif position == "C0":
#         print(f"C0")
#         write_read(b'C0')
#     elif position == "C1":
#         print(f"C1")
#         write_read(b'C1')
#     elif position == "C2":
#         print(f"C2")
#         write_read(b'C2')
#     elif position == "C3":
#         print(f"C3")
#         write_read(b'C3')
#     elif position == "C4":
#         print(f"C4")
#         write_read(b'C4')
#     elif position == "C5":
#         print(f"C5")
#         write_read(b'C5')
#     elif position == "C6":
#         print(f"C6")
#         write_read(b'C6')
#     elif position == "C7":
#         print(f"C7")
#         write_read(b'C7')
#     else:
#         print("Bin: '{}' does not exist!".format(position))
    
#     #running = False

    
# def on_queue_snapshot(doc_snap, changes, read_time):
    
#     arr = []
#     #global running
#     running = True
#     #enter the loop only if there are any items in collection on change
#     for doc in doc_snap:
#         if doc.id != "0":
#             curr_request = doc.to_dict() #save curr request to send right data to history record
#             curr_request["id"] = doc.id 
#             is_alexa = curr_request["is_alexa"] #check if alexa
            
#             # route for links between collection is: History -> Items -> Bin 
#             hist_ref = db.collection(u"History").document(u'{}'.format(curr_request["history_id"])) # first, history
#             hist_doc = hist_ref.get()
#             if hist_doc.exists:
                
#                 hist_doc_dict = hist_doc.to_dict()
#                 items_ref = db.collection(u"Items").document(u'{}'.format(hist_doc_dict["item_id"])) # second, items
#                 items_doc = items_ref.get()
#                 if items_doc.exists:

#                     # branch for alexa because it needs rfid verification
#                     if is_alexa:
#                         ### RFID Verification ###
#                         id = ''
#                         while True:
#                             #print("Please use rfid tag")
#                             id, text = rfid.read()
#                             break

#                         user_docs = db.collection(u'Users').stream()
#                         for user in user_docs:
#                             user_dict = user.to_dict()
#                             if user_dict["rfid_tag"] == id:
#                                 #print("user found")
#                                 hist_ref.set({
#                                     u'user_id': user.id
#                                 }, merge=True)
#                            #else:
#                                 #print("Please register RFID tag to user!")
                        
#                         # send bin to read_write function to be sent to arduino
#                         process_request(items_doc.to_dict()["bin_id"])
#                         #print(curr_request["id"])
#                         db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete() #delete queued item
#                     else:

#                         # no verification since its from phone
#                         process_request(items_doc.to_dict()["bin_id"])
#                         #print(curr_request)
#                         db.collection(u'Requests').document(u'{}'.format(curr_request["id"])).delete()
                    
                    
#                 #else:
#                     #print(u'item_id: {} does not exist!'.format(hist_doc_dict["item_id"]))
#             #else:
#                 #print(u'history_id: {} does not exist!'.format(curr_request["history_id"]))
#     #else:
#         #print("No requests!")
#     #running = False

# def on_rfid_snapshot(doc_snap, changes, read_time):
#     for doc in doc_snap:
#         docDict = doc.to_dict()
#         if docDict['live'] == True:
#             #print("Please use rfid tag")
#             while True:
#                 id, text = rfid.read()
#                 #print(id)
#                 break
#             db.collection(u'Users').document(u'{}'.format(docDict["userid"])).update({ "rfid_tag": id })
#             db.collection(u'RFIDinit').document(u'VTflY8VUypi61GVplO8p').update({ "live": False, "userid": "" })


# queue_ref = db.collection(u"Requests")
# rfid_ref = db.collection(u"RFIDinit").document(u"VTflY8VUypi61GVplO8p")

# queue_watch = queue_ref.on_snapshot(on_queue_snapshot)
# rfid_watch = rfid_ref.on_snapshot(on_rfid_snapshot)

app = Flask(__name__)

# #ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
# data_queue = queue.Queue()





# define a function that continuously reads from the serial port and puts the data in the queue
#def serial_reader():
    #global running
    #while True:
        #data = ser.readline().decode('utf-8').rstrip()
        #print("Received data:", data)  # add this line
        #if data == '1':
        #   running = False
        #  print("Yay")
            
        
        #data_queue.put(data)

# # start the serial reader thread
#serial_thread = threading.Thread(target=serial_reader)
#serial_thread.daemon = True
#serial_thread.start()

# define the warning route
@app.route('/warning')
def warning():
    return render_template('warning.html')

# define the ready route
@app.route('/ready')
def ready():
    return render_template('ready.html')

# define the index route
@app.route('/')
def index():
    # global running
    # print(running)
    with open('data.txt', 'r') as file:
        value = ast.literal_eval(file.read().strip())
    if value:
        return render_template('warning.html')
    else:
        return render_template('ready.html')


if __name__ == '__main__':
    app.run(debug=True)
