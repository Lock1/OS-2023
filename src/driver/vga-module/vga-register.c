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

// Mono use 0x3B4-0x3B5 instead
const struct VGARegisterPort _vga_reg_crt_controller = {
    .address_register = 0x3D4,
    .data_register    = 0x3D5,
};



// Video Mode 13h register values
const struct VGACRTControllerHorizontalTotalData _vga_reg_mode13h_horizontal_total = {
    .horizontal_total = 3,
};

const struct VGACRTControllerEndHorizontalDisplayData _vga_reg_mode13h_end_horizontal_display = {
    .end_horizontal_display = 0,
};

const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking = {
    .start_horizontal_blanking = 3,
};

const struct VGACRTControllerEndHorizontalBlankingData _vga_reg_mode13h_end_horizontal_blanking = {
    .end_horizontal_blanking = 0,
    .display_enable_skew     = 0,
    .vertical_rectrace       = 0,
};

const struct VGAExternalOutputRegisterData _vga_reg_mode13h_output = {
    .ioas             = 1,
    .ram_enable       = 1,
    .clock_select     = 0,
    .odd_even_page    = 1,
    .horizontal_sync  = 1,
    .vertical_sync    = 0,
};

const struct VGAExternalFeatureControlData _vga_reg_mode13h_fc = {
    .feature_control0 = 0,
    .feature_control1 = 0,
};