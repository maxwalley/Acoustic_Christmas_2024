import cv2
import mediapipe as mp
import pyo
import threading
import time

audio_freq = 440
audio_lock = threading.Lock()

def audio_runner(stop_event):
    global audio_freq
    s = pyo.Server().boot()
    s.start()

    freq_signal = pyo.Sig(audio_freq)  # Frequency signal for the oscillator
    osc = pyo.Sine(freq=freq_signal, mul=0.5).out()

    #Keep audio running, updating frequency if necessary
    while not stop_event.is_set():
        with audio_lock:
            freq_signal.value = audio_freq  # Update frequency safely
        time.sleep(0.1)  # Small delay to reduce CPU usage

stop_event = threading.Event()

audio_thread_instance = threading.Thread(target=audio_runner, args=(stop_event,))
audio_thread_instance.start()

# Initialize MediaPipe Hands and drawing utility
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

# Set up webcam video capture
cap = cv2.VideoCapture(0)

# Configure MediaPipe Hands
with mp_hands.Hands(
    static_image_mode=False,       # Real-time detection
    max_num_hands=2,              # Detect up to 2 hands
    min_detection_confidence=0.5, # Minimum confidence for detection
    min_tracking_confidence=0.5   # Minimum confidence for tracking
) as hands:

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            print("Ignoring empty camera frame.")
            continue

        frame = cv2.flip(frame, 1)

        # Convert the frame to RGB (MediaPipe works with RGB images)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Process the frame and detect hands
        results = hands.process(frame_rgb)

        # Draw hand landmarks if hands are detected
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(
                    frame, hand_landmarks, mp_hands.HAND_CONNECTIONS
                )

                wrist = hand_landmarks.landmark[mp_hands.HandLandmark.WRIST]

                # Get the normalized x, y positions
                x_norm = wrist.x  # Normalized x (0 to 1)
                y_norm = wrist.y

                y_norm = 1.0 - y_norm - 0.1

                y_norm = y_norm * 1800 + 200

                if(y_norm < 200):
                    y_norm = 200

                with audio_lock:
                    audio_freq = y_norm

        # Display the output frame
        cv2.imshow('Hand Detection', frame)

        # Exit the loop when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release resources
    cap.release()
    cv2.destroyAllWindows()
    stop_event.set()
    audio_thread_instance.join()