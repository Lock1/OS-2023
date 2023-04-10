# Python 3 - Create new 256 color palette
from PIL import Image
import sys

src        = Image.new(mode="HSV", size=(256, 256), color=(0, 0, 0))
pixelarray = src.load()
output     = open(sys.argv[1], "w") if len(sys.argv) > 1 and __name__ == "__main__" else open("palette.c", "w")

# Mode 13h - Palette mapping
# Warning : VGA is only 6-bit, need to compress
# 0: BIOS color attribute row
# 1: Monochrome row

# 0x20 to 0x67 - (72 color, nicely span over 24x3) First color intensity (Highest intensity)
# 0x68 to 0xAF - Second color intensity
# 0xB0 to 0xF7 - Third color intensity

# 0xF8 to 0xFF - Unused / Black

# TODO : This is quick solution, better just make purely custom palette

# Using HSV color space
CUTOFF_BLACK       = 4
INTENSITY_DIVISOR  = 86  # 256 / 3
SATURATION_DIVISOR = 86  # 256 / 3
HUE_DIVISOR        = 11  # 256 / 24

def set_box(x, y, color):
    for i in range(16):
        for j in range(16):
            pixelarray[x + i, y + j] = color

# Creating image in HSV color space
for i in range(16):
    for j in range(16):
        index = i*16 + j
        if 0x10 <= index < 0x20:
            # Plain grayscale
            color = (0, 0, (index-0x10)*16)
        elif 0x20 <= index < 0xF8:
            temp       = index - 0x20
            value      = temp // 0x48
            temp       = temp % 0x48
            saturation = temp // 0x18
            hue        = (temp % 0x18)
            
            saturation = 0.5 if saturation == 0 else saturation 
            value      = 0.5 if value == 0 else value 
            color      = ((170+int(hue*11)) % 256, 255-int(saturation*86), 255-int(value*86))
        else:
            color = (0, 0, 0)
        set_box(16*j, 16*i, color)

# Writing and compressing 8-bit RGB image to 6-bit color space
src        = src.convert(mode="RGB")
pixelarray = src.load()
for i in range(16):
    line = ""
    for j in range(16):
        r, g, b = pixelarray[16*j, 16*i]
        # Divided by 4, 8-bit color space -> 6-bit color space map
        line += f"0x{r//4:=02X}, 0x{g//4:=02X}, 0x{b//4:=02X}, "
    output.write(f"{line}\n")

if __name__ == "__main__":
    src.show()