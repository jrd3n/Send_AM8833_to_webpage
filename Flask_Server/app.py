from flask import Flask, render_template
from flask_socketio import SocketIO
import socket
import json

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your-secret-key'
socketio = SocketIO(app)

UDP_IP = "0.0.0.0"  # Listen on all available network interfaces
UDP_PORT = 1234     # Port to listen on

@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('connect')
def handle_connect():
    print('Client connected')

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')

def receive_udp():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))

    while True:
        data, addr = sock.recvfrom(1024)
        temperature_values = data.decode().split()

        # Convert the temperature values to float
        temperature_values = [float(temp) for temp in temperature_values]

        # Create an 8x8 matrix from the temperature values
        matrix = [temperature_values[i:i+8] for i in range(0, len(temperature_values), 8)]

        # Create a JSON object with the matrix
        json_data = json.dumps(matrix)
        # print("Received message:")
        #   print(json_data)

        socketio.emit('udp_message', json_data)  # Emit UDP message to connected clients

if __name__ == '__main__':
    import threading
    udp_thread = threading.Thread(target=receive_udp)
    udp_thread.start()
    # socketio.run(app)
    app.run(host='0.0.0.0')