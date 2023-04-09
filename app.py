from flask import Flask, render_template
import serial
import threading
import queue

app = Flask(__name__)
ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
data_queue = queue.Queue()

# define a function that continuously reads from the serial port and puts the data in the queue
def serial_reader():
    while True:
        data = ser.readline().decode('utf-8').rstrip()
        data_queue.put(data)

# start the serial reader thread
serial_thread = threading.Thread(target=serial_reader)
serial_thread.daemon = True
serial_thread.start()

# define the index route
@app.route('/')
def index():
    data = ''
    if not data_queue.empty():
        data = data_queue.get()
    return render_template('index.html', data=data)

if __name__ == '__main__':
    app.run(debug=True)
