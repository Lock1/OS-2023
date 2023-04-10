# Python 3 - Convert image to ".sis format" (Raw mode 13h pixel value)
# https://pillow.readthedocs.io/en/4.0.x/reference/Image.html
from PIL import Image
import sys
import struct

# Mode 13h : 320x200
src        = Image.open(sys.argv[1])
src        = src.resize((320, 200)).convert(mode="HSV")
pixelarray = src.load()
output     = open(sys.argv[2], "wb")

# Mode 13h - Palette mapping
# 0: BIOS color attribute row
# 1: Monochrome row

# 0x20 to 0x67 - (72 color, nicely span over 24x3) First color intensity (Highest intensity)
# 0x68 to 0xAF - Second color intensity
# 0xB0 to 0xF7 - Third color intensity

# 0xF8 to 0xFF - Unused / Black


# Using HSV color space
CUTOFF_BLACK                = 10
CUTOFF_SATURATION_GRAYSCALE = 35
INTENSITY_DIVISOR           = 86  # 256 / 3
SATURATION_DIVISOR          = 86  # 256 / 3
HUE_DIVISOR                 = 11  # 256 / 24


for j in range(src.height):
    for i in range(src.width):
        hue, saturation, value = pixelarray[i,j]
        byte_to_write          = 0
        if value < CUTOFF_BLACK:
            byte_to_write = 0   # Assuming the 0 index is black
        elif saturation < CUTOFF_SATURATION_GRAYSCALE:
            byte_to_write = 0x10 + (value//16)
        else:
            intensity_index  = (255-value) // INTENSITY_DIVISOR
            saturation_index = (255-saturation) // SATURATION_DIVISOR
            hue_index        = ((130-hue) % 256) // HUE_DIVISOR
            assert 0 <= hue_index        <= 24, f"{hue_index}"
            assert 0 <= saturation_index <   3, f"{saturation_index}"
            assert 0 <= intensity_index  <   3, f"{intensity_index}"
            # print(f"{hue_index}, {saturation_index}, {intensity_index}")
            byte_to_write    = 0x20 + 0x48*intensity_index + 0x18*saturation_index + hue_index 

        output.write(struct.pack("B", byte_to_write))