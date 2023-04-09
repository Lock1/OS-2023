#include "lib-header/driver/vga/register/color.h"
#include "lib-header/driver/vga/vga-register.h"

const uint8_t _vga_reg_mode_13h_color_palette[256*3] = {
    00, 00, 00, 00, 10, 41, 12, 28, 18,  2, 43, 22, 35, 19,  9, 58, 
    00, 00, 57, 35, 12, 43, 43, 47, 24, 24, 28, 20, 24, 60, 10, 60, 
    15, 31, 47, 63, 62, 56, 20, 60, 56, 22, 63, 61, 36, 63, 63, 63, 
    00, 00, 00,  5,  5,  5,  8,  8,  8, 11, 11, 11, 14, 14, 14, 17, 
    17, 17, 20, 20, 20, 24, 24, 24, 28, 28, 28, 32, 32, 32, 36, 36, 
    36, 40, 40, 40, 45, 45, 45, 50, 50, 50, 56, 56, 56, 63, 63, 63, 
    13, 12, 15, 15, 16, 22, 17, 20, 29, 19, 24, 36, 21, 28, 43, 23, 
    31, 50, 25, 34, 57, 26, 42, 63, 00, 15,  2,  1, 22,  4,  2, 29, 
     6,  3, 36,  8,  4, 43, 10,  5, 50, 12,  6, 57, 14, 20, 63, 40, 
    18,  6,  7, 25, 12, 11, 33, 17, 14, 40, 23, 18, 48, 28, 21, 55, 
    34, 25, 62, 39, 27, 63, 48, 36, 15,  3,  2, 22,  6,  4, 29,  9, 
     6, 36, 12,  8, 43, 15, 10, 50, 18, 12, 57, 21, 14, 63, 28, 20, 
    15, 00, 00, 22,  7, 00, 29, 15, 00, 36, 23, 00, 43, 31, 00, 50,
    39, 00, 57, 47, 00, 63, 55, 00, 15,  5,  3, 22, 11,  7, 29, 17, 
    11, 36, 23, 15, 43, 29, 19, 50, 35, 23, 57, 41, 27, 63, 53, 34, 
    28, 14, 12, 33, 20, 14, 38, 26, 16, 43, 32, 18, 48, 38, 20, 53, 
    44, 22, 58, 50, 24, 63, 56, 30,  5,  5,  6, 10, 10, 13, 15, 15, 
    20, 20, 20, 27, 25, 25, 34, 30, 30, 41, 35, 35, 48, 44, 44, 63, 
     3,  6,  5,  5, 11,  9,  7, 16, 13,  9, 21, 17, 11, 26, 21, 13, 
    31, 25, 15, 36, 29, 20, 48, 38,  6,  6,  7, 13, 13, 15, 20, 20, 
    23, 27, 27, 31, 34, 34, 39, 41, 41, 47, 48, 48, 55, 57, 57, 63, 
     6, 15,  4, 12, 22,  8, 18, 29, 12, 24, 36, 16, 30, 43, 20, 36, 
    50, 24, 42, 57, 28, 54, 63, 35, 15, 10, 10, 22, 16, 16, 29, 21, 
    21, 36, 27, 27, 43, 32, 32, 50, 38, 38, 57, 43, 43, 63, 54, 54, 
    15, 15,  6, 22, 22, 12, 29, 29, 18, 36, 36, 24, 43, 43, 30, 50, 
    50, 36, 57, 57, 42, 63, 63, 54,  2,  4, 14,  6, 12, 21, 10, 20,
    28, 14, 28, 35, 18, 36, 42, 22, 44, 49, 26, 52, 56, 36, 63, 63, 
    18,  4, 14, 24,  8, 21, 31, 12, 28, 37, 16, 35, 44, 20, 42, 50, 
    24, 49, 57, 28, 56, 63, 38, 63, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 53, 44, 22, 
     9,  8, 12, 16, 14, 16, 22, 21, 20, 29, 27, 24, 35, 34, 28, 42, 
    40, 32, 48, 47, 36, 57, 56, 43,  8, 12, 16, 14, 16, 22, 21, 20, 
    29, 27, 24, 35, 34, 28, 42, 40, 32, 48, 47, 36, 57, 56, 43, 63, 
    13, 9,  11, 21, 16, 15, 27, 22, 18, 36, 29, 22, 42, 35, 25, 51, 
    42, 29, 57, 48, 32, 63, 56, 39,  6, 14,  9, 12, 21, 14, 18, 27, 
    22, 24, 33, 28, 30, 39, 36, 36, 46, 42, 42, 52, 47, 50, 59, 53, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
};

const struct VGARegisterPort _vga_reg_port_color_write_mode = {
    .data_register    = 0x3C8,
};

const struct VGARegisterPort _vga_reg_port_color_data = {
    .data_register    = 0x3C9,
};

void vga_set_mode_13h_palette(void) {
    for (uint32_t i = 0; i < 256; i++) {
        vga_set_unindexed_register(_vga_reg_port_color_write_mode, (uint8_t) i);

        vga_set_unindexed_register(_vga_reg_port_color_data, _vga_reg_mode_13h_color_palette[i*3 + 0]);
        vga_set_unindexed_register(_vga_reg_port_color_data, _vga_reg_mode_13h_color_palette[i*3 + 1]);
        vga_set_unindexed_register(_vga_reg_port_color_data, _vga_reg_mode_13h_color_palette[i*3 + 2]);
    }
}