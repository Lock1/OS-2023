# Python 3 - Convert video to ".ter format" (2-bit color space video format)
import cv2
import sys
import struct
import threading
import time
import itertools

# Rule:
# - Each frame consist of exactly 64000 length data (sum of all entry length)
# - Each 2-bytes is called "Entry", which contain RLE information
# - Entry: 1 top-most-bit for color + 15-bit for length (max 2**15)

def open_cv2_show_img(img):
    cv2.imshow("Show Image", frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def frame_ter_encoder(frame) -> bytes:
    result_frame  = b""
    linear_frame  = frame.flatten(order="C")
    length        = 0
    total_length  = 0
    current_color = linear_frame[0]
    for i in range(320*200):
        if linear_frame[i] == current_color:
            length       += 1
            total_length += 1
        if linear_frame[i] != current_color or length == 2**15-1 or i == 320*200-1:
            raw_byte     = min(current_color, 1) << 15 | length
            result_frame += struct.pack("<H", raw_byte)
            # Reset
            length = 0
            if linear_frame[i] != current_color:
                length       = 1
                total_length += 1
            current_color = linear_frame[i]

    assert total_length == 320*200, f"{total_length}"
    return result_frame


capture    = cv2.VideoCapture(sys.argv[1])
framecount = int(capture.get(cv2.CAP_PROP_FRAME_COUNT))
print(f"Source file : {sys.argv[1]}")
print(f"Framecount  : {framecount}")


progress      = 0
current_frame = 0
start_time    = time.time()
filesize      = 0
elapsed_time  = 0
run_thread    = True
logger        = threading.Thread(target=
    lambda: [
        time.sleep(1) or 
        print(f"[{elapsed_time//60}:{elapsed_time%60:02}] Progress: {progress:.2f}% ({current_frame}/{framecount}) - {filesize} bytes") or
        run_thread or sys.exit(0)
        for _ in itertools.count()
    ]
)
logger.start()



with open(sys.argv[2], "wb") as file:
    for i in range(1000, 2500, 5):
        elapsed_time  = int(time.time() - start_time)
        current_frame = i + 1
        progress      = current_frame * 100 / framecount
        capture.set(1, i)
        _, frame         = capture.read()
        frame            = cv2.resize(frame, (320, 200))
        frame            = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        threshold, frame = cv2.threshold(frame, 127, 255, cv2.THRESH_BINARY)
        frame_bytes      = frame_ter_encoder(frame)
        filesize         += len(frame_bytes)
        file.write(frame_bytes)


run_thread = False

