#include "lib-header/cpu/portio.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/color.h"
#include "lib-header/driver/vga/video-mode-preset/vga-video-preset.h"
#include "lib-header/stdmem.h"

// Default video mode is 3
uint8_t _vga_current_video_mode = 3;

// TODO : Modular design for any video mode
// TODO : Massive struct containing all of register value for modularity

// TODO : All pixel and framebuffer should in framebuffer instead, vga.c is only for VGA register programming
void vga_mode_13h_put_pixel(uint32_t x, uint32_t y, uint8_t color) {
    uint8_t *addr = (uint8_t *) 0xC00A0000 + (320*y) + x;
    *addr = color;
}

void vga_use_video_mode_13h(void) {
    vga_set_external_register(&_vga_preset_mode_13h_external);
    vga_set_sequencer_register(&_vga_preset_mode_13h_sequencer);
    vga_set_crt_controller_register(&_vga_preset_mode_13h_crt_controller);
    vga_set_graphics_register(&_vga_preset_mode_13h_graphics);
    vga_set_attribute_controller_register(&_vga_preset_mode_13h_attribute_controller);
    vga_set_mode_13h_palette();
    _vga_current_video_mode = 0x13;
}
