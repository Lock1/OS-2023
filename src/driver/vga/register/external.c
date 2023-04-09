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



void vga_set_mode_13h_external_register(const struct VGAExternalRegister *external) {
    vga_set_unindexed_register(_vga_reg_port_external_output, register_const_serialize(&external->output));
    vga_set_unindexed_register(_vga_reg_port_external_fc, register_const_serialize(&external->feature_control));
}