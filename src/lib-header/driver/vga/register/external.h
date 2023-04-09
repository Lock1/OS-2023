#ifndef _VGA_EXTERNAL_REGISTER_H
#define _VGA_EXTERNAL_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"

// Register datas
struct VGAExternalOutputRegisterData {
    uint8_t ioas:            1;
    uint8_t ram_enable:      1;
    uint8_t clock_select:    2;
    uint8_t _reserved:       1;
    uint8_t odd_even_page:   1;
    uint8_t horizontal_sync: 1;
    uint8_t vertical_sync:   1;
} __attribute__((packed));

struct VGAExternalFeatureControlData {
    uint8_t feature_control0: 1;
    uint8_t feature_control1: 1;
    uint8_t _reserved:        6;
} __attribute__((packed));



// VGA register port
extern const struct VGARegisterPort               _vga_reg_port_external_output;
extern const struct VGARegisterPort               _vga_reg_port_external_fc;

// Video Mode 13h values
extern const struct VGAExternalOutputRegisterData _vga_reg_mode13h_output;
extern const struct VGAExternalFeatureControlData _vga_reg_mode13h_fc;

void vga_set_external_register(void);

#endif

