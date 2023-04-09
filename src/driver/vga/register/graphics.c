#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Indexed register
const struct VGARegisterPort _vga_reg_port_graphics = {
    .address_register = 0x3CE,
    .data_register    = 0x3CF,
};

// Video Mode 13h register values
const struct VGAGraphicsSetResetData              _vga_reg_mode13h_set_reset = {
    .plane_0_set_reset = 0,
    .plane_1_set_reset = 0,
    .plane_2_set_reset = 0,
    .plane_3_set_reset = 0,
};

const struct VGAGraphicsEnableSetResetData        _vga_reg_mode13h_enable_set_reset = {
    .plane_0_enable_set_reset = 0,
    .plane_1_enable_set_reset = 0,
    .plane_2_enable_set_reset = 0,
    .plane_3_enable_set_reset = 0,
};
const struct VGAGraphicsColorCompareData          _vga_reg_mode13h_color_compare = {
    .plane_0_color_compare = 0,
    .plane_1_color_compare = 0,
    .plane_2_color_compare = 0,
    .plane_3_color_compare = 0,
};
const struct VGAGraphicsDataRotateData            _vga_reg_mode13h_data_rotate = {
    .logical_operation = 0,
    .rotate_count      = 0,
};
const struct VGAGraphicsReadMapSelectData         _vga_reg_mode13h_read_map_select = {
    .read_map_select = 0,
};



const struct VGAGraphicsGraphicsModeData          _vga_reg_mode13h_graphics_mode = {
    .write_mode          = 0,
    .read_mode           = 0,
    .host_even_odd       = 0,
    .interleave_register = 0,
    .color_shift_256     = 1,
};
const struct VGAGraphicsMiscellaneousGraphicsData _vga_reg_mode13h_miscellaneous_graphics = {
    .alphanumeric_disable = 1,
    .chain_even_odd       = 0,
    .memory_map_select    = 1,
};
const struct VGAGraphicsColorDontCareData         _vga_reg_mode13h_color_dont_care = {
    .plane_0_color_dont_care = 1,
    .plane_1_color_dont_care = 1,
    .plane_2_color_dont_care = 1,
    .plane_3_color_dont_care = 1,
};
const struct VGAGraphicsBitMaskData               _vga_reg_mode13h_bit_mask = {
    .bit_mask = 0xFF,
};



void vga_set_graphics_register(void) {
    uint8_t graphics_index[9] = {
        GRAPHICS_INDEX_SET_RESET,
        GRAPHICS_INDEX_ENABLE_SET_RESET,
        GRAPHICS_INDEX_COLOR_COMPARE,
        GRAPHICS_INDEX_DATA_ROTATE,
        GRAPHICS_INDEX_READ_MAP_SELECT,
        GRAPHICS_INDEX_GRAPHICS_MODE,
        GRAPHICS_INDEX_MISCELLANEOUS_GRAPHICS,
        GRAPHICS_INDEX_COLOR_DONT_CARE,
        GRAPHICS_INDEX_BIT_MASK,
    };
    uint8_t graphics_data[9] = {
        register_const_serialize(&_vga_reg_mode13h_set_reset),
        register_const_serialize(&_vga_reg_mode13h_enable_set_reset),
        register_const_serialize(&_vga_reg_mode13h_color_compare),
        register_const_serialize(&_vga_reg_mode13h_data_rotate),
        register_const_serialize(&_vga_reg_mode13h_read_map_select),
        register_const_serialize(&_vga_reg_mode13h_graphics_mode),
        register_const_serialize(&_vga_reg_mode13h_miscellaneous_graphics),
        register_const_serialize(&_vga_reg_mode13h_color_dont_care),
        register_const_serialize(&_vga_reg_mode13h_bit_mask),
    };

    set_indexed_register(_vga_reg_port_graphics, graphics_index, graphics_data, 9);
}