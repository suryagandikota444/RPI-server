from firebase_admin import credentials, firestore
import firebase_admin
from flask import Flask, render_template, request, jsonify
import ast
import os
import random

app = Flask(__name__)
cred = credentials.Certificate("/home/pi/Documents/RPI-server/csce483-capstone-firebase-adminsdk-oef2p-34a354f736.json")
firebase_admin.initialize_app(cred)

db = firestore.client()

# define the index route
# @app.route('/')
# def index():
#     with open('data.txt', 'r') as file:
#         value = ast.literal_eval(file.read().strip())

#     with open('data2.txt', 'r') as file2:
#         value2 = ast.literal_eval(file2.read().strip())

#     if value:
#         return render_template('warning.html')
#     elif not value and value2:
#         if request.method == 'POST' and 'clicked' in request.form:
#             return render_template('ready.html') 
#     elif not value and not value2:
#         return render_template('button2.html')
#     else:
#         return render_template('ready.html')
    
#     return render_template('ready.html')
    
@app.route('/')
def index():
    return render_template('ready.html')

@app.route('/get_text_file_value')
def get_text_file_value():
    if os.path.exists("/home/pi/Documents/AS/data.txt"):
        with open("/home/pi/Documents/AS/data.txt", "r") as f:
            value = f.read().strip()
        return jsonify(value=value)
    else:
        return jsonify(value=None)

@app.route('/set_false', methods=['POST'])
def set_false():
    with open('/home/pi/Documents/AS/data.txt', 'w') as f:
        f.write("False")
    return jsonify(status='success')   

if __name__ == '__main__':
    try:
        app.run(debug=True, port=5002)
    except:
        app.run(debug=True, port=random.randint(5010, 6000))
