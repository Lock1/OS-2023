#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Attribute controller registers - Unindexed
const struct VGARegisterPort _vga_reg_port_attribute_controller = {
    .data_register    = 0x3C0,
};

// Datas
const struct VGAAttributeControllerIndexData                  _vga_reg_attribute_controller_index_array[ATTRIBUTE_CONTROLLER_REGISTER_COUNT] = {
    [0]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_0, .palette_address_source = 0},
    [1]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_1, .palette_address_source = 0},
    [2]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_2, .palette_address_source = 0},
    [3]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_3, .palette_address_source = 0},
    [4]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_4, .palette_address_source = 0},
    [5]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_5, .palette_address_source = 0},
    [6]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_6, .palette_address_source = 0},
    [7]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_7, .palette_address_source = 0},
    [8]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_8, .palette_address_source = 0},
    [9]  = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_9, .palette_address_source = 0},
    [10] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_A, .palette_address_source = 0},
    [11] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_B, .palette_address_source = 0},
    [12] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_C, .palette_address_source = 0},
    [13] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_D, .palette_address_source = 0},
    [14] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_E, .palette_address_source = 0},
    [15] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_PALLETE_F, .palette_address_source = 0},

    [16] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_ATTRIBUTE_MODE_CONTROL,   .palette_address_source = 0},
    [17] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_OVERSCAN_COLOR,           .palette_address_source = 0},
    [18] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_COLOR_PLANE_ENABLE,       .palette_address_source = 0},
    [19] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_HORIZONTAL_PIXEL_PANNING, .palette_address_source = 0},
    [20] = {.attribute_address = ATTRIBUTE_CONTROLLER_INDEX_COLOR_SELECT,             .palette_address_source = 0},
};
const struct VGAAttributeControllerPaletteData                _vga_reg_mode13h_palette_array[ATTRIBUTE_CONTROLLER_PALETTE_COUNT] = {
    [0]  = {.internal_palette_index = 0x0},
    [1]  = {.internal_palette_index = 0x1},
    [2]  = {.internal_palette_index = 0x2},
    [3]  = {.internal_palette_index = 0x3},
    [4]  = {.internal_palette_index = 0x4},
    [5]  = {.internal_palette_index = 0x5},
    [6]  = {.internal_palette_index = 0x6},
    [7]  = {.internal_palette_index = 0x7},

    [8]  = {.internal_palette_index = 0x8},
    [9]  = {.internal_palette_index = 0x9},
    [10] = {.internal_palette_index = 0xA},
    [11] = {.internal_palette_index = 0xB},
    [12] = {.internal_palette_index = 0xC},
    [13] = {.internal_palette_index = 0xD},
    [14] = {.internal_palette_index = 0xE},
    [15] = {.internal_palette_index = 0xF},
};

const struct VGAAttributeControllerAttributeModeControlData   _vga_reg_mode13h_attribute_mode_control = {
    .attribute_controller_graphics_enable = 1,
    .monochrome_emulation                 = 0,
    .line_graphics                        = 0,
    .blink_enable                         = 0,
    .pixel_panning_mode                   = 0,
    .color_8_bit_mode                     = 1,
    .palette_bit_5_4                      = 0,
};
const struct VGAAttributeControllerOverscanColorData          _vga_reg_mode13h_overscan_color = {
    .overscan_palette_index = 0,
};
const struct VGAAttributeControllerColorPlaneEnableData       _vga_reg_mode13h_color_plane_enable = {
    .plane_0_color_plane_enable = 1,
    .plane_1_color_plane_enable = 1,
    .plane_2_color_plane_enable = 1,
    .plane_3_color_plane_enable = 1,
};
const struct VGAAttributeControllerHorizontalPixelPanningData _vga_reg_mode13h_horizontal_pixel_panning = {
    .pixel_shift_count = 0,
};
const struct VGAAttributeControllerColorSelectData            _vga_reg_mode13h_color_select = {
    .color_select_5_4 = 0,
    .color_select_7_6 = 0,
};


void vga_set_attribute_controller_register(void) {
    uint8_t attribute_controller_data[ATTRIBUTE_CONTROLLER_REGISTER_COUNT] = {
        [0 ... ATTRIBUTE_CONTROLLER_PALETTE_COUNT-1] = 0,
        register_const_serialize(&_vga_reg_mode13h_attribute_mode_control),
        register_const_serialize(&_vga_reg_mode13h_overscan_color),
        register_const_serialize(&_vga_reg_mode13h_color_plane_enable),
        register_const_serialize(&_vga_reg_mode13h_horizontal_pixel_panning),
        register_const_serialize(&_vga_reg_mode13h_color_select),
    };

    for (uint32_t i = 0; i < ATTRIBUTE_CONTROLLER_PALETTE_COUNT; i++)
        attribute_controller_data[i] = register_const_serialize(&_vga_reg_mode13h_palette_array[i]);

    // Read external register 0x3DA to force attribute controller switch into index state
    vga_read_unindexed_register(_vga_reg_port_external_fc);

    for (uint32_t i = 0; i < ATTRIBUTE_CONTROLLER_REGISTER_COUNT; i++) {
        vga_read_unindexed_register(_vga_reg_port_attribute_controller);
        // Send index first then data on exact same port
        vga_set_unindexed_register(_vga_reg_port_attribute_controller, register_const_serialize(&_vga_reg_attribute_controller_index_array[i]));
        vga_set_unindexed_register(_vga_reg_port_attribute_controller, attribute_controller_data[i]);
    }
}