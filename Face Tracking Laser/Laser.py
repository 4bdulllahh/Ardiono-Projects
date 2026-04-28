import cv2
import serial
import time

# --- CONFIGURATION ---
ARDUINO_PORT = 'COM4' 
BAUD_RATE = 9600

# Connect to Arduino
try:
    arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) 
    print("Connected to Arduino!")
except Exception as e:
    print(f"Failed to connect to Arduino on {ARDUINO_PORT}. Error: {e}")
    exit()

# Load the face detection model
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Open Webcam
cap = cv2.VideoCapture(0)
WIDTH = 640
HEIGHT = 480
cap.set(3, WIDTH)
cap.set(4, HEIGHT)

def map_range(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

last_pan_angle = 90
tilt_stop_value = 90 # Make sure this matches the stop value in your Arduino code

print("Running... Press 'q' in the video window to quit.")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    if len(faces) > 0:
        (x, y, w, h) = faces[0]
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
        
        face_center_x = x + (w // 2)
        face_center_y = y + (h // 2)
        
        # X-Axis (180 Motor): Fixed Left/Right Tracking
        pan_angle = map_range(face_center_x, 0, WIDTH, 0, 180) 
        last_pan_angle = pan_angle
        
        # Y-Axis (360 Motor): Visual Feedback Control
        center_y = HEIGHT // 2
        error_y = face_center_y - center_y
        
        tilt_speed = tilt_stop_value 
        deadzone = 40   # Pixel buffer so it doesn't jitter
        
        # Increased speed to 20 for faster vertical tracking
        if error_y > deadzone:
            tilt_speed = tilt_stop_value - 20 # Spin down
        elif error_y < -deadzone:
            tilt_speed = tilt_stop_value + 20 # Spin up

        command = f"{pan_angle},{tilt_speed}\n"
        arduino.write(command.encode('utf-8'))
    
    else:
        # No face found: Hold X-axis steady, STOP Y-axis spinning
        command = f"{last_pan_angle},{tilt_stop_value}\n"
        arduino.write(command.encode('utf-8'))

    cv2.imshow("Face Tracker", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()