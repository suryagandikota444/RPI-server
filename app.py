from flask import Flask, render_template
import serial

app = Flask(__name__)
ser = serial.Serial('/dev/ttyACM0', 9600)  # replace with your Arduino port and baud rate

@app.route('/')
def index():
    data = ser.readline().decode('utf-8').rstrip()  # read a line of data from the serial port
    return render_template('index.html', data=data)

if __name__ == '__main__':
    app.run(debug=True)
