from PIL import Image
import sys
import struct

drawn_image   = Image.new(mode="RGB", size=(320, 200), color=(0, 0, 0))
pixelarray    = drawn_image.load()


word_count   = 0
current_iter = 0
with open(sys.argv[1], "rb") as target:
    word = target.read(2)
    print(hex(struct.unpack("<H", word)[0]), bin(struct.unpack("<H", word)[0]))
    while word:
        word_count += 1
        encoded_byte = struct.unpack("<H", word)[0]
        color        = 255 if encoded_byte & 0x80 else 0
        length       = encoded_byte & 0x7F
        for i in range(length):
            pixelarray[(current_iter + i) % 320, (current_iter + i) // 320] = (color, color, color)
        current_iter += length
        word = target.read(2)

print(current_iter, word_count)
drawn_image.show()