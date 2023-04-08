#ifndef _VGA_REGISTER_H
#define _VGA_REGISTER_H

#include "lib-header/stdtype.h"

// Note : Naming convention directly follow from http://www.osdever.net/FreeVGA/vga/vga.htm


struct VGARegisterPort {
    uint16_t address_register;
    uint16_t data_register;
};

// http://www.osdever.net/FreeVGA/vga/extreg.htm
struct VGAMiscOutputRegisterData {
    uint8_t ioas:            1;
    uint8_t ram_enable:      1;
    uint8_t clock_select:    2;
    uint8_t _reserved:       1;
    uint8_t odd_even_page:   1;
    uint8_t horizontal_sync: 1;
    uint8_t vertical_sync:   1;
};

struct VGAMiscFeatureControlData {
    uint8_t feature_control0: 1;
    uint8_t feature_control1: 1;
    uint8_t _reserved: 6;
};


// External / Misc registers, http://www.osdever.net/FreeVGA/vga/extreg.htm
extern const struct VGARegisterPort _vga_reg_external_output;
extern const struct VGARegisterPort _vga_reg_external_fc;

// Video Mode 13h values
extern const struct VGAMiscOutputRegisterData _vga_reg_mode13h_misc;
extern const struct VGAMiscFeatureControlData _vga_reg_mode13h_fc;


#endif