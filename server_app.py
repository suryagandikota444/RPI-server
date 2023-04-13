
from flask import Flask, render_template
import ast


app = Flask(__name__)


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
    with open('data.txt', 'r') as file:
        value = ast.literal_eval(file.read().strip())
    if value:
        return render_template('warning.html')
    else:
        return render_template('ready.html')

if __name__ == '__main__':
    app.run(debug=True, port=5001)
