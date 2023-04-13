
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

    with open('data2.txt', 'r') as file2:
        value2 = ast.literal_eval(file2.read().strip())

    if value:
        return render_template('warning.html')
    elif not value and value2:
        if request.method == 'POST' and 'clicked' in request.form:
            return render_template('ready.html')
    elif not value and not value2:
        return render_template('button2.html')
    else:
        return render_template('ready.html')
    
    
    
    

if __name__ == '__main__':
    app.run(debug=True, port=5001)