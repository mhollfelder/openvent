from flask import Flask
from flask import render_template

app = Flask(__name__)

import data
d = data.exampledata()
d.start_update_loop()

@app.route('/')
def get_index():
    return render_template('index.html')

@app.route('/exampledata/v2/docu')
def get_doku_v2():
    return render_template('api_v2_doku.html')

@app.route('/exampledata/v1/')
def get_data_v1():
    return d.get_v1()

@app.route('/exampledata/v2/data')
def get_data_v2():
    return d.get_v2()
