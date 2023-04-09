#include "lib-header/driver/vga/register/color.h"
#include "lib-header/driver/vga/vga-register-programmer.h"

const struct VGARegisterPort _vga_reg_port_color_write_mode = {
    .data_register    = 0x3C8,
};

const struct VGARegisterPort _vga_reg_port_color_data = {
    .data_register    = 0x3C9,
};



void vga_set_palette(const uint8_t *palette_array, uint32_t color_count) {
    for (uint32_t i = 0; i < color_count; i++) {
        vga_set_single_port_register(_vga_reg_port_color_write_mode, (uint8_t) i);

        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 0]);
        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 1]);
        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 2]);
    }
}