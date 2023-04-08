#include "lib-header/vga-register.h"

// static const struct VGARegister graphics_register = {
//     .address_register = 0x3CE,
//     .data_register    = 0x3CF,
// };

// VGA Register port
const struct VGARegisterPort _vga_reg_external_output = {
    .data_register    = 0x3C2,
};

// Assuming color mode is used, for mono use 0x3BA
const struct VGARegisterPort _vga_reg_external_fc = {
    .data_register    = 0x3DA,
};



// Video Mode 13h register values
const struct VGAMiscOutputRegisterData _vga_reg_mode13h_misc = {
    .ioas             = 1,
    .ram_enable       = 1,
    .clock_select     = 0,
    .odd_even_page    = 1,
    .horizontal_sync  = 1,
    .vertical_sync    = 0,
};

const struct VGAMiscFeatureControlData _vga_reg_mode13h_fc = {
    .feature_control0 = 0,
    .feature_control1 = 0,
};