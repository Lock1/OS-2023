#ifndef _VGA_PRESET_MODE_3H
#define _VGA_PRESET_MODE_3H

#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/color.h"

#define MODE_3H_MEMORY_FRAMEBUFFER  (uint8_t *) 0xC00B8000
#define MODE_3H_RESOLUTION          (80*25)


#endif