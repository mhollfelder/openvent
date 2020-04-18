import json, time, random
from flask import jsonify
from _thread import start_new_thread, allocate_lock

# Set up logging
import logging
logging.basicConfig(level=logging.DEBUG, filename="data.log", format='%(asctime)s\t%(name)s\t%(levelname)s\t%(message)s', datefmt='%Y-%m-%d %H:%M:%S')
logger = logging.getLogger(__name__)

# Helper functions for JSON IO

def dump_to_file( content, file ):
    with open(file, 'w') as f:
        json.dump(content, f)

def read_from_file( file ):
    with open(file, 'r') as f:
        return json.load(f)

def update_simple_continous(current_value, mean_value, deviation_factor, max_change_factor):
        abs_change = random.uniform(-deviation_factor*current_value, deviation_factor*current_value)
        new_value = current_value + abs_change
        if abs(new_value - mean_value) > mean_value*max_change_factor:
            new_value = current_value - abs_change
        return round(new_value, 2)

# Exampledata generation

class exampledata():
    def __init__(self):
        self.update_delay = 1
        self.data_lock = allocate_lock()
        self.data_v1 = read_from_file( 'data_v1.txt' )
        self.data = read_from_file( 'data.txt' )
        '''
        self.data = {
            "0":{
            "device_id":4242,
            "time": 0,
            "processed":{
                "volumePerMovement": 220, # fest
                "frequency": 10, # fest
                "volumePerMinute": 2200, # berechnet #done
                "MVe":4500, # berechnet
                "ventilationMode": "Pressure Control",
                "ExpiredCO2":40, # +- 10% # done
                "ExpiredO2":5, # +- 10% # done
                "triggerSettings":{
                "FiO2": 60,
                "humidity": 50,
                "pressure_max": 40,
                "MVe": 4000,
                "RR": 12,
                "VT": 325,
                "PEEP": 6.10,
                "IE":1.4
                }
            },
            "raw":{
                "pressure1": 35, # berechnet
                "pressure2": 36, # berechnet
                "temperature1": 31, # +- 10% # done
                "temperature2": 30, # +- 10% # done
                "CO2": 5, # +- 10% # done
                "O2": 40, # +- 10% # done
                "angleSensor": 320, # mit rpm
                "current": 50, # mit rpm
                "motorRPM": 100 # frequenz
            }
            }
        }
        '''

    def update_data(self):
        for key in self.data:
            # Real values:
            self.data[key]["time"] = int(time.time())

            # Simple random values:
            self.data[key]["raw"]["temperature1"] = update_simple_continous(self.data[key]["raw"]["temperature1"], 26.00, 0.01, 0.12)
            self.data[key]["raw"]["temperature2"] = update_simple_continous(self.data[key]["raw"]["temperature2"], 26.00, 0.01, 0.12)
            self.data[key]["raw"]["O2"] = update_simple_continous(self.data[key]["raw"]["O2"], 40, 0.02, 0.08)
            self.data[key]["raw"]["CO2"] = update_simple_continous(self.data[key]["raw"]["CO2"], 5, 0.02, 0.08)
            self.data[key]["processed"]["ExpiredCO2"] = self.data[key]["raw"]["CO2"]
            self.data[key]["processed"]["ExpiredO2"] = self.data[key]["raw"]["O2"]

            # Calculated values:
            self.data[key]["processed"]["volumePerMinute"] = self.data[key]["processed"]["frequency"] * self.data[key]["processed"]["volumePerMovement"]

    def update_loop(self):
        while True:
            try:
                self.data_lock.acquire()
                self.update_data()
                self.data_lock.release()
                time.sleep(self.update_delay)
            except Exception as e:
                logger.error(e) # Logging exception, because otherwise its silent in thread.

    def start_update_loop(self):
        start_new_thread( self.update_loop, () )
    
    def get_v1(self):
        self.data_v1["0"]["time"] = int(time.time())
        return jsonify(self.data_v1)

    def get_v2(self):
        self.data_lock.acquire()
        ret = self.data
        self.data_lock.release()
        return jsonify(ret)

# Test the output:
'''
ed = exampledata()
while True:
    ed.start_update_loop()
    time.sleep(1)
    print(ed.data)
'''