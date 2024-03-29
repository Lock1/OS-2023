#ifndef _VGA_GRAPHICS_REGISTER_H
#define _VGA_GRAPHICS_REGISTER_H

#include "lib-header/driver/vga/vga-register-programmer.h"
#include "lib-header/stdtype.h"

// Constant & indices
#define GRAPHICS_REGISTER_COUNT               9

#define GRAPHICS_INDEX_SET_RESET              0
#define GRAPHICS_INDEX_ENABLE_SET_RESET       1
#define GRAPHICS_INDEX_COLOR_COMPARE          2
#define GRAPHICS_INDEX_DATA_ROTATE            3
#define GRAPHICS_INDEX_READ_MAP_SELECT        4
#define GRAPHICS_INDEX_GRAPHICS_MODE          5
#define GRAPHICS_INDEX_MISCELLANEOUS_GRAPHICS 6
#define GRAPHICS_INDEX_COLOR_DONT_CARE        7
#define GRAPHICS_INDEX_BIT_MASK               8



// Register datas
struct VGAGraphicsSetResetData {
    uint8_t plane_0_set_reset: 1;
    uint8_t plane_1_set_reset: 1;
    uint8_t plane_2_set_reset: 1;
    uint8_t plane_3_set_reset: 1;
    uint8_t _reserved:         4;
} __attribute__((packed));

struct VGAGraphicsEnableSetResetData {
    uint8_t plane_0_enable_set_reset: 1;
    uint8_t plane_1_enable_set_reset: 1;
    uint8_t plane_2_enable_set_reset: 1;
    uint8_t plane_3_enable_set_reset: 1;
    uint8_t _reserved:                4;
} __attribute__((packed));

struct VGAGraphicsColorCompareData {
    uint8_t plane_0_color_compare: 1;
    uint8_t plane_1_color_compare: 1;
    uint8_t plane_2_color_compare: 1;
    uint8_t plane_3_color_compare: 1;
    uint8_t _reserved:             4;
} __attribute__((packed));

struct VGAGraphicsDataRotateData {
    uint8_t rotate_count:      3;
    uint8_t logical_operation: 2;
    uint8_t _reserved:         3;
} __attribute__((packed));

struct VGAGraphicsReadMapSelectData {
    uint8_t read_map_select: 2;
    uint8_t _reserved:       6;
} __attribute__((packed));

struct VGAGraphicsGraphicsModeData {
    uint8_t write_mode:          2;
    uint8_t _reserved_1:         1;
    uint8_t read_mode:           1;
    uint8_t host_even_odd:       1;
    uint8_t interleave_register: 1;
    uint8_t color_shift_256:     1;
    uint8_t _reserved_2:         1;
} __attribute__((packed));

struct VGAGraphicsMiscellaneousGraphicsData {
    uint8_t alphanumeric_disable: 1;
    uint8_t chain_even_odd:       1;
    uint8_t memory_map_select:    2;
    uint8_t _reserved:            4;
} __attribute__((packed));

struct VGAGraphicsColorDontCareData {
    uint8_t plane_0_color_dont_care: 1;
    uint8_t plane_1_color_dont_care: 1;
    uint8_t plane_2_color_dont_care: 1;
    uint8_t plane_3_color_dont_care: 1;
    uint8_t _reserved:               4;
} __attribute__((packed));

struct VGAGraphicsBitMaskData {
    uint8_t bit_mask;
} __attribute__((packed));

struct VGAGraphicsRegister {
    struct VGAGraphicsSetResetData              set_reset;
    struct VGAGraphicsEnableSetResetData        enable_set_reset;
    struct VGAGraphicsColorCompareData          color_compare;
    struct VGAGraphicsDataRotateData            data_rotate;
    struct VGAGraphicsReadMapSelectData         read_map_select;

    struct VGAGraphicsGraphicsModeData          graphics_mode;
    struct VGAGraphicsMiscellaneousGraphicsData miscellaneous_graphics;
    struct VGAGraphicsColorDontCareData         color_dont_care;
    struct VGAGraphicsBitMaskData               bit_mask;
} __attribute__((packed));



extern const struct VGARegisterPort                      _vga_reg_port_graphics;



void vga_set_graphics_register(const struct VGAGraphicsRegister *graphics);

#endif

