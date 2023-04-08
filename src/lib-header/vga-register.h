#ifndef _VGA_REGISTER_H
#define _VGA_REGISTER_H

#include "lib-header/stdtype.h"

struct VGARegister {
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

// Special register, using 0x3C2 for write-only data port
// Use instead 0x3CC for read-only port
// http://www.osdever.net/FreeVGA/vga/extreg.htm
extern const struct VGARegister misc_output_register;

// Video Mode 13h values
extern const struct VGAMiscOutputRegisterData misc_mode13h;

#endif