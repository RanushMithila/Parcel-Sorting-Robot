import cv2
import requests
import numpy as np
import pytesseract
from PIL import Image

# ESP32-CAM URL for video streaming
url = "http://192.168.43.161:81/stream"

# Tesseract OCR configuration
ocrConfig = r'--psm 3 --oem 3'

# Create a VideoCapture object to read frames from the stream
cap = cv2.VideoCapture(url)

while True:
    # Read a frame from the stream
    ret, frame = cap.read()

    if not ret:
        print("Error reading frame from stream")
        break

    # Convert the frame to PIL Image format
    pil_image = Image.fromarray(frame)

    # Perform OCR on the image using pytesseract
    text = pytesseract.image_to_string(pil_image, config=ocrConfig)

    # Print the recognized text
    print(text)

    # Display the original frame
    cv2.imshow("Original Frame", frame)

    # Exit the loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the VideoCapture and close any open windows
cap.release()
cv2.destroyAllWindows()
