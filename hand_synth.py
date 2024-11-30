import cv2
import mediapipe as mp
import pyo
import threading
import time

max_oscillators = 40
oscillator_params = [[0, 0, threading.Lock()] for _ in range(max_oscillators)]

def audio_runner(stop_event):
    global audio_freq
    s = pyo.Server().boot()

    signals = [(pyo.Sig(1000), pyo.Sig(0.0)) for _ in range(max_oscillators)]
    oscillators = [pyo.Sine(freq=freq, mul=mul).out() for freq, mul in signals]

    s.start()

    #Keep audio running, updating frequency if necessary
    while not stop_event.is_set():

        for index, params in enumerate(oscillator_params):
            with params[2]:
                signals[index][0].value = params[0]
                signals[index][1].value = params[1]
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
    max_num_hands=max_oscillators,              # Detect up to 2 hands
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

            num_osc = len(results.multi_hand_landmarks)

            if(num_osc > max_oscillators):
                num_osc = max_oscillators

            for index, osc in enumerate(oscillator_params):
                if index >= num_osc:
                    with oscillator_params[index][2]:
                        oscillator_params[index][1] = 0.0

            for index, hand_landmarks in enumerate(results.multi_hand_landmarks):
                mp_drawing.draw_landmarks(
                    frame, hand_landmarks, mp_hands.HAND_CONNECTIONS
                )

                if index >= max_oscillators:
                    break

                wrist = hand_landmarks.landmark[mp_hands.HandLandmark.WRIST]

                # Get the normalized x, y positions
                x_norm = wrist.x  # Normalized x (0 to 1)
                y_norm = wrist.y

                y_norm = 1.0 - y_norm - 0.1

                y_norm = y_norm * 1800 + 200

                if(y_norm < 100):
                    y_norm = 100

                with oscillator_params[index][2]:
                    oscillator_params[index][0] = y_norm
                    oscillator_params[index][1] = (1.0 / num_osc) / 2.0

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