import threading
from flask import Flask
import cv2
from pyzbar import pyzbar
import requests


def read_qr():
    # ESP32-CAM URL for video streaming
    url = "http://192.168.43.161:81/stream"
    resChange = "http://192.168.43.161/control?var=framesize&val=7"
    ledOn = "http://192.168.43.161/control?var=led_intensity&val=175"
    exit = False
    
    res = requests.get(resChange)
    led = requests.get(ledOn)
    print("Resolution set:", res.status_code)
    print("Led ON:", led.status_code)

    # Create a VideoCapture object to read frames from the stream
    cap = cv2.VideoCapture(url)

    while True:
        # Read a frame from the stream
        ret, frame = cap.read()

        if not ret:
            print("Error reading frame from stream")
            break

        # Convert the frame to grayscale for QR code detection
        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect QR codes in the grayscale frame
        qr_codes = pyzbar.decode(gray_frame)

        # Process detected QR codes
        for qr_code in qr_codes:
            # Extract the QR code data
            qr_data = qr_code.data.decode("utf-8")
            if (qr_data == "Polonnaruwa"):
                qr_data = "9"
            elif (qr_data == "Colombo"):
                qr_data = "8"
            elif (qr_data == "Trincomalee"):
                qr_data = "7"
            elif (qr_data == "Gampaha"):
                qr_data = "6"
            else:
                qr_data ="5"
            
            # Print the QR code data
            print(qr_data)
            x = requests.get("http://192.168.43.161:85/data?qr_data="+qr_data)
            print(x.text)
            if (x.text == "Data received"):
                exit = True
            # break

            # Draw a rectangle around the QR code
            (x, y, w, h) = qr_code.rect
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Draw the QR code data on the frame
            cv2.putText(frame, qr_data, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

        # Display the frame
        cv2.imshow("RMB", frame)
        
        if (exit):
            break
        # Exit the loop when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the VideoCapture and close any open windows
    cap.release()
    cv2.destroyAllWindows()

app = Flask(__name__)

    
@app.route('/camera', methods=['GET'])
def turn_on():
    print("turning it on")
    thread = threading.Thread(target=read_qr)
    thread.start()
    timeout_duration = 10
    thread.join(timeout_duration)
    if thread.is_alive():
        return '5'
    else:
        return 'ON'

if __name__ == '__main__':
    app.run(host='0.0.0.0')