#ifndef _VGA_ATTRIBUTE_CONTROLLER_REGISTER_H
#define _VGA_ATTRIBUTE_CONTROLLER_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"


// Constants & indices
#define ATTRIBUTE_CONTROLLER_REGISTER_COUNT                 21
#define ATTRIBUTE_CONTROLLER_PALETTE_COUNT                  16

#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_0                0
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_1                1
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_2                2
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_3                3
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_4                4
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_5                5
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_6                6
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_7                7

#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_8                8
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_9                9
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_A                0xA
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_B                0xB
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_C                0xC
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_D                0xD
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_E                0xE
#define ATTRIBUTE_CONTROLLER_INDEX_PALLETE_F                0xF

#define ATTRIBUTE_CONTROLLER_INDEX_ATTRIBUTE_MODE_CONTROL   0x10
#define ATTRIBUTE_CONTROLLER_INDEX_OVERSCAN_COLOR           0x11
#define ATTRIBUTE_CONTROLLER_INDEX_COLOR_PLANE_ENABLE       0x12
#define ATTRIBUTE_CONTROLLER_INDEX_HORIZONTAL_PIXEL_PANNING 0x13
#define ATTRIBUTE_CONTROLLER_INDEX_COLOR_SELECT             0x14


// Register datas
struct VGAAttributeControllerIndexData {
    uint8_t attribute_address:      5;
    uint8_t palette_address_source: 1;
    uint8_t _reserved:              2;
} __attribute__((packed));

struct VGAAttributeControllerPaletteData {
    uint8_t internal_palette_index: 6;
    uint8_t _reserved:              2;
} __attribute__((packed));

struct VGAAttributeControllerAttributeModeControlData {
    uint8_t attribute_controller_graphics_enable: 1;
    uint8_t monochrome_emulation:                 1;
    uint8_t line_graphics:                        1;
    uint8_t blink_enable:                         1;
    uint8_t _reserved:                            1;
    uint8_t pixel_panning_mode:                   1;
    uint8_t color_8_bit_mode:                     1;
    uint8_t palette_bit_5_4:                      1;
} __attribute__((packed));

struct VGAAttributeControllerOverscanColorData {
    uint8_t overscan_palette_index;
} __attribute__((packed));

struct VGAAttributeControllerColorPlaneEnableData {
    uint8_t plane_0_color_plane_enable: 1;
    uint8_t plane_1_color_plane_enable: 1;
    uint8_t plane_2_color_plane_enable: 1;
    uint8_t plane_3_color_plane_enable: 1;
    uint8_t _reserved:                  4;
} __attribute__((packed));

struct VGAAttributeControllerHorizontalPixelPanningData {
    uint8_t pixel_shift_count: 4;
    uint8_t _reserved:         4;
} __attribute__((packed));

struct VGAAttributeControllerColorSelectData {
    uint8_t color_select_5_4: 2;
    uint8_t color_select_7_6: 2;
    uint8_t _reserved:        4;
} __attribute__((packed));



// VGA register port
extern const struct VGARegisterPort                                  _vga_reg_port_attribute_controller;

// Video Mode 13h values
extern const struct VGAAttributeControllerIndexData                  _vga_reg_mode13h_index_array[ATTRIBUTE_CONTROLLER_REGISTER_COUNT];
extern const struct VGAAttributeControllerPaletteData                _vga_reg_mode13h_palette_array[ATTRIBUTE_CONTROLLER_PALETTE_COUNT];

extern const struct VGAAttributeControllerAttributeModeControlData   _vga_reg_mode13h_attribute_mode_control;
extern const struct VGAAttributeControllerOverscanColorData          _vga_reg_mode13h_overscan_color;
extern const struct VGAAttributeControllerColorPlaneEnableData       _vga_reg_mode13h_color_plane_enable;
extern const struct VGAAttributeControllerHorizontalPixelPanningData _vga_reg_mode13h_horizontal_pixel_panning;
extern const struct VGAAttributeControllerColorSelectData            _vga_reg_mode13h_color_select;

void vga_set_attribute_controller_register(void);

#endif
