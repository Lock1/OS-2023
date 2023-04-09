#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/vga-register-programmer.h"

// VGA Register port - Attribute controller registers - indexed
const struct VGARegisterPort _vga_reg_port_attribute_controller = {
    .data_register    = 0x3C0,
};

const struct VGARegisterPort _vga_reg_port_attribute_controller_read = {
    .data_register    = 0x3C1,
};

const struct VGAAttributeControllerIndexData _vga_reg_attribute_controller_index_array[ATTRIBUTE_CONTROLLER_REGISTER_COUNT] = {
    [0]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_0,                .palette_address_source = 0},
    [1]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_1,                .palette_address_source = 0},
    [2]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_2,                .palette_address_source = 0},
    [3]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_3,                .palette_address_source = 0},
    [4]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_4,                .palette_address_source = 0},
    [5]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_5,                .palette_address_source = 0},
    [6]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_6,                .palette_address_source = 0},
    [7]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_7,                .palette_address_source = 0},
    [8]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_8,                .palette_address_source = 0},
    [9]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_9,                .palette_address_source = 0},
    [10] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_A,                .palette_address_source = 0},
    [11] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_B,                .palette_address_source = 0},
    [12] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_C,                .palette_address_source = 0},
    [13] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_D,                .palette_address_source = 0},
    [14] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_E,                .palette_address_source = 0},
    [15] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_F,                .palette_address_source = 0},

    [16] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_ATTRIBUTE_MODE_CONTROL,   .palette_address_source = 0},
    [17] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_OVERSCAN_COLOR,           .palette_address_source = 0},
    [18] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_COLOR_PLANE_ENABLE,       .palette_address_source = 0},
    [19] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_HORIZONTAL_PIXEL_PANNING, .palette_address_source = 0},
    [20] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_COLOR_SELECT,             .palette_address_source = 0},
};



void vga_set_attribute_controller_register(const struct VGAAttributeControllerRegister *attribute) {
    uint8_t attribute_controller_data[ATTRIBUTE_CONTROLLER_REGISTER_COUNT] = {
        [0 ... ATTRIBUTE_CONTROLLER_PALETTE_COUNT-1] = 0,
        register_const_serialize(&attribute->attribute_mode_control),
        register_const_serialize(&attribute->overscan_color),
        register_const_serialize(&attribute->color_plane_enable),
        register_const_serialize(&attribute->horizontal_pixel_panning),
        register_const_serialize(&attribute->color_select),
    };

    for (uint32_t i = 0; i < ATTRIBUTE_CONTROLLER_PALETTE_COUNT; i++)
        attribute_controller_data[i] = register_const_serialize(&attribute->palette_array[i]);

    // Read external register 0x3DA to force attribute controller switch into index state
    vga_read_single_port_register(_vga_reg_port_external_fc);

    for (uint32_t i = 0; i < ATTRIBUTE_CONTROLLER_REGISTER_COUNT; i++) {
        vga_read_single_port_register(_vga_reg_port_attribute_controller);
        // Send index first then data on exact same port
        vga_set_single_port_register(_vga_reg_port_attribute_controller, register_const_serialize(&_vga_reg_attribute_controller_index_array[i]));
        vga_set_single_port_register(_vga_reg_port_attribute_controller, attribute_controller_data[i]);
    }
    
    // Tell VGA controller to load palette register and lock any change to register
    struct VGAAttributeControllerIndexData load_palette_index = {
        .attribute_address      = 0,
        .palette_address_source = 1,
    };
    vga_set_single_port_register(_vga_reg_port_attribute_controller, register_const_serialize(&load_palette_index));
}