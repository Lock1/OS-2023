#include "lib-header/cpu/portio.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/color.h"
#include "lib-header/driver/vga/register/text/font.h"
#include "lib-header/driver/vga/video-mode-preset/vga-video-preset.h"
#include "lib-header/stdmem.h"

// Default video mode is 3
uint8_t _vga_current_video_mode = 3;

void vga_use_video_mode_13h(void) {
    vga_set_external_register(&_vga_preset_mode_13h_external);
    vga_set_sequencer_register(&_vga_preset_mode_13h_sequencer);
    vga_set_crt_controller_register(&_vga_preset_mode_13h_crt_controller);
    vga_set_graphics_register(&_vga_preset_mode_13h_graphics);
    vga_set_attribute_controller_register(&_vga_preset_mode_13h_attribute_controller);
    vga_set_palette(_vga_preset_mode_13h_color_palette, MODE_13H_COLOR);
    _vga_current_video_mode = 0x13;
}

void vga_use_video_mode_3h(void) {
    vga_set_external_register(&_vga_preset_mode_3h_external);
    vga_set_sequencer_register(&_vga_preset_mode_3h_sequencer);
    vga_set_crt_controller_register(&_vga_preset_mode_3h_crt_controller);
    vga_set_graphics_register(&_vga_preset_mode_3h_graphics);
    vga_set_attribute_controller_register(&_vga_preset_mode_3h_attribute_controller);
    vga_load_standard_vga_font();
    vga_set_palette(_vga_preset_mode_3h_color_palette, MODE_3H_COLOR);
    _vga_current_video_mode = 0x03;
}