#ifndef _VGA_COLOR_REGISTER_H
#define _VGA_COLOR_REGISTER_H

#include "lib-header/driver/vga/vga-register-programmer.h"
#include "lib-header/stdtype.h"

// Indexed register but only 1 port

extern const struct VGARegisterPort _vga_reg_port_color_write_mode;
extern const struct VGARegisterPort _vga_reg_port_color_data;



// TODO : Insane? Struct for palette
// Color count is how many triplet of RGB
void vga_set_palette(const uint8_t *palette_array, uint32_t color_count);

#endif