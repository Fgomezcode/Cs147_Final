from flask import Flask, render_template, request
from turbo_flask import Turbo
import time
import threading

app = Flask(__name__)

turbo = Turbo(app)

def update_load():
    with app.app_context():
        while True:
            time.sleep(5)
            turbo.push(turbo.replace(render_template('update.html'), 'Sensor_Values'))
            turbo.push(turbo.replace(render_template('chart.html'), 'Chart_Values'))
            

with app.app_context():
    threading.Thread(target=update_load).start()


@app.context_processor
def inject_load():
    lines = []
    with open('esp_data.txt', 'r') as f:       
        lines = f.readlines()                         
        f.close()   
    
    return {'sensorTemperature':lines[0],'sensorHumidity':lines[1] ,'sensorSoil': lines[2],
            'sensorDayLight': lines[3]}  

@app.route("/", methods = ['POST', 'GET'])
def home():
    receivedData = request.values   

    data = [('temp', receivedData.get("temp")), ('hum', receivedData.get("hum")), ('soil', receivedData.get("soil")), ('daylight', receivedData.get("daylight"))]
    labels = [row[0] for row in data]
    values = [row[1] for row in data]

    print(labels)
    print(values)
    
    if request.method == 'POST':                    # this is when the sensor data arrives.
        
        if "Water Button" in request.form:
            with open('commands.txt', 'w') as f: 
                print('Will Water...')
                f.write('Water')
                f.close()
            return 'Water'
        
        elif "Mist Button" in request.form:
            with open('commands.txt', 'w') as f: 
                print('Will Mist...')
                f.write('Mist')
                f.close()
            return 'Mist'

        try:
            with open('esp_data.txt', 'w') as f:        # we need to write this to a file 
                f.write(f'{receivedData.get("temp")}\n')                 
                f.write(f'{receivedData.get("hum")}\n')
                f.write(f'{receivedData.get("soil")}\n')
                f.write(f'{receivedData.get("daylight")}\n')
                f.close()
                
            with open('commands.txt', 'r') as f:
                print('getting command')
                temp = f.readline()
                f.close()

            with open('commands.txt', 'w') as f:
                print('Turn Off water')
                f.write('Do Nothing')
                f.close()

        except:
            pass
        return temp
                    
    return render_template('home.html', values = values) # render the contents of test.html for the visitor, pass the value we read from file
                                                    # 'Received $data_value