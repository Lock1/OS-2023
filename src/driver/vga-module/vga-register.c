#include "lib-header/vga-register.h"

// static const struct VGARegister graphics_register = {
//     .address_register = 0x3CE,
//     .data_register    = 0x3CF,
// };

const struct VGARegister misc_output_register = {
    .data_register    = 0x3C2,
};

const struct VGAMiscOutputRegisterData misc_mode13h = {
    .ioas            = 1,
    .ram_enable      = 1,
    .clock_select    = 0,
    .odd_even_page   = 1,
    .horizontal_sync = 1,
    .vertical_sync   = 0,
};
