from PIL import Image
import sys
import importlib
import struct

palette_maker = importlib.import_module("palette-maker-256")
target        = open(sys.argv[1], "rb")

drawn_image   = Image.new(mode="RGB", size=(320, 200), color=(0, 0, 0))
pixelarray    = drawn_image.load()

for j in range(200):
    for i in range(320):
        encoded_byte = struct.unpack("B", target.read(1))[0]
        color        = palette_maker.pixelarray[16*(encoded_byte%16), 16*(encoded_byte//16)]
        pixelarray[i, j] = color

drawn_image.show()