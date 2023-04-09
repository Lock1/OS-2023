#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - External registers
const struct VGARegisterPort _vga_reg_port_external_output = {
    .data_register    = 0x3C2,
};

// Assuming color mode is used, for mono use 0x3BA
const struct VGARegisterPort _vga_reg_port_external_fc = {
    .data_register    = 0x3DA,
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

void vga_set_external_register(void) {
    vga_set_unindexed_register(_vga_reg_port_external_output, register_const_serialize(&_vga_reg_mode13h_output));
    vga_set_unindexed_register(_vga_reg_port_external_fc, register_const_serialize(&_vga_reg_mode13h_fc));
}