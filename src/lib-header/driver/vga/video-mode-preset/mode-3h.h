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
#define MODE_3H_COLOR               16

extern const struct VGAExternalRegister            _vga_preset_mode_3h_external;
extern const struct VGASequencerRegister           _vga_preset_mode_3h_sequencer;
extern const struct VGACRTControllerRegister       _vga_preset_mode_3h_crt_controller;
extern const struct VGAGraphicsRegister            _vga_preset_mode_3h_graphics;
extern const struct VGAAttributeControllerRegister _vga_preset_mode_3h_attribute_controller;
extern const uint8_t                               _vga_preset_mode_3h_color_palette[MODE_3H_COLOR*3];

#endif