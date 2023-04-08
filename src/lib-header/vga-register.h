#ifndef _VGA_REGISTER_H
#define _VGA_REGISTER_H

#include "lib-header/stdtype.h"

#define CRT_INDEX_HORIZONTAL_TOTAL          0
#define CRT_INDEX_END_HORIZONTAL_DISPLAY    0
#define CRT_INDEX_START_HORIZONTAL_BLANKING 0
#define CRT_INDEX_END_HORIZONTAL_BLANKING   0

// Note : Naming convention directly follow from http://www.osdever.net/FreeVGA/vga/vga.htm

struct VGARegisterPort {
    uint16_t   address_register;
    uint16_t   data_register;
} __attribute__((packed));


// VGA Register values, avoiding raw bytes and use struct as much as possible, even if somewhat feel stupid
struct VGACRTControllerHorizontalTotalData {
    uint8_t horizontal_total;
} __attribute__((packed));

struct VGACRTControllerEndHorizontalDisplayData {
    uint8_t end_horizontal_display;
} __attribute__((packed));

struct VGACRTControllerStartHorizontalBlankingData {
    uint8_t start_horizontal_blanking;
} __attribute__((packed));

struct VGACRTControllerEndHorizontalBlankingData {
    uint8_t end_horizontal_blanking: 5;
    uint8_t display_enable_skew:     2;
    uint8_t vertical_rectrace:       1;
} __attribute__((packed));

// http://www.osdever.net/FreeVGA/vga/extreg.htm
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
extern const struct VGARegisterPort _vga_reg_crt_controller;

// External / Misc registers, http://www.osdever.net/FreeVGA/vga/extreg.htm
extern const struct VGARegisterPort _vga_reg_external_output;
extern const struct VGARegisterPort _vga_reg_external_fc;

// Video Mode 13h values
extern const struct VGACRTControllerHorizontalTotalData         _vga_reg_mode13h_horizontal_total;
extern const struct VGACRTControllerEndHorizontalDisplayData    _vga_reg_mode13h_end_horizontal_display;
extern const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking;
extern const struct VGACRTControllerEndHorizontalBlankingData   _vga_reg_mode13h_end_horizontal_blanking;
extern const struct VGAExternalOutputRegisterData _vga_reg_mode13h_output;
extern const struct VGAExternalFeatureControlData _vga_reg_mode13h_fc;


#endif