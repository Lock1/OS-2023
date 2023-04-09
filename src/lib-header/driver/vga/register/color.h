#ifndef _VGA_COLOR_REGISTER_H
#define _VGA_COLOR_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"

// Indexed register but only 1 port

extern const struct VGARegisterPort _vga_reg_port_color_write_mode;
extern const struct VGARegisterPort _vga_reg_port_color_data;

extern const uint8_t _vga_reg_mode_13h_color_palette[256*3];

void vga_set_mode_13h_palette(void);

#endif