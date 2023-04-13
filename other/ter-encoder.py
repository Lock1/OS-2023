# Python 3 - Convert video to ".ter format" (2-bit color space video format)
import cv2
import sys
import struct
import threading
import time
import itertools

# Holy crap i just remember RLE is extremely efficient for relatively uniform data
# Rule:
# - Each frame consist of exactly 64000 length data (sum of all entry length)
# - Each 2-bytes is called "Entry", which contain RLE information
# - Entry: 1 top-most-bit for color + 15-bit for length (max 2**15)

def open_cv2_show_img(img):
    cv2.imshow("Show Image", frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def frame_ter_encoder(frame) -> bytes:
    pass

capture    = cv2.VideoCapture(sys.argv[1])
framecount = int(capture.get(cv2.CAP_PROP_FRAME_COUNT))
print(f"Source file : {sys.argv[1]}")
print(f"Framecount  : {framecount}")


progress      = 0
current_frame = 0
start_time    = time.time()
elapsed_time  = 0
run_thread    = True
logger        = threading.Thread(target=
    lambda: [
        time.sleep(1) or 
        print(f"[{elapsed_time//60}:{elapsed_time%60}] Progress: {progress:.2f}% ({current_frame}/{framecount})") or
        run_thread or sys.exit(0)
        for _ in itertools.count()
    ]
)
logger.start()



with open(sys.argv[2], "wb") as file:
    for i in range(framecount):
        elapsed_time  = int(time.time() - start_time)
        current_frame = i + 1
        progress      = current_frame * 100 / framecount
        capture.set(1, i)
        _, frame = capture.read()
        frame    = cv2.resize(frame, (320, 200))
        frame    = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        # TODO : Encode


run_thread = False

