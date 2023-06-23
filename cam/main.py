import cv2

url = 'http://192.168.43.161:81/stream'

cap = cv2.VideoCapture(url)

while True:
    ret, frame = cap.read()
    if frame is not None:
        cv2.imshow('frame', frame)
    q = cv2.waitKey(1)
    if q == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
