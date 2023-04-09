#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Indexed register
const struct VGARegisterPort _vga_reg_port_graphics = {
    .address_register = 0x3CE,
    .data_register    = 0x3CF,
};



void vga_set_graphics_register(const struct VGAGraphicsRegister *graphics) {
    uint8_t graphics_index[GRAPHICS_REGISTER_COUNT] = {
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
    uint8_t graphics_data[GRAPHICS_REGISTER_COUNT] = {
        register_const_serialize(&graphics->set_reset),
        register_const_serialize(&graphics->enable_set_reset),
        register_const_serialize(&graphics->color_compare),
        register_const_serialize(&graphics->data_rotate),
        register_const_serialize(&graphics->read_map_select),
        register_const_serialize(&graphics->graphics_mode),
        register_const_serialize(&graphics->miscellaneous_graphics),
        register_const_serialize(&graphics->color_dont_care),
        register_const_serialize(&graphics->bit_mask),
    };

    set_indexed_register(_vga_reg_port_graphics, graphics_index, graphics_data, GRAPHICS_REGISTER_COUNT);
}