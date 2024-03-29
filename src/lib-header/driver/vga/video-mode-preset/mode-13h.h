#ifndef _VGA_PRESET_MODE_13H
#define _VGA_PRESET_MODE_13H

#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/color.h"

#define MODE_13H_MEMORY_FRAMEBUFFER (uint8_t *) 0xC00A0000
#define MODE_13H_RESOLUTION         (320*200)
#define MODE_13H_COLOR              256

extern const struct VGAExternalRegister            _vga_preset_mode_13h_external;
extern const struct VGASequencerRegister           _vga_preset_mode_13h_sequencer;
extern const struct VGACRTControllerRegister       _vga_preset_mode_13h_crt_controller;
extern const struct VGAGraphicsRegister            _vga_preset_mode_13h_graphics;
extern const struct VGAAttributeControllerRegister _vga_preset_mode_13h_attribute_controller;
extern const uint8_t                               _vga_preset_mode_13h_color_palette[MODE_13H_COLOR*3];
extern const uint8_t                               _vga_preset_mode_13h_bubach_color_palette[MODE_13H_COLOR*3];

#endif