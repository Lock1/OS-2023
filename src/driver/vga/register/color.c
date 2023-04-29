#include "lib-header/driver/vga/register/color.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/vga-register-programmer.h"

const struct VGARegisterPort _vga_reg_port_color_write_mode = {
    .data_register    = 0x3C8,
};

const struct VGARegisterPort _vga_reg_port_color_data = {
    .data_register    = 0x3C9,
};


// TODO : It seems color is weird?
void vga_set_palette(const uint8_t *palette_array, uint32_t color_count) {
    for (uint32_t i = 0; i < color_count; i++) {
        uint8_t index = 0;
        if (color_count == 16) {
            // For text mode, we need to reprogram attribute controller register
            vga_read_single_port_register(_vga_reg_port_external_fc);
            vga_set_single_port_register(_vga_reg_port_attribute_controller, (uint8_t) i);
            index = vga_read_single_port_register(_vga_reg_port_attribute_controller_read);
        } else {
            index = (uint8_t) i;
        }
        vga_set_single_port_register(_vga_reg_port_color_write_mode, index);

        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 0]);
        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 1]);
        vga_set_single_port_register(_vga_reg_port_color_data, palette_array[i*3 + 2]);
    }
    if (color_count == 16) {
        vga_read_single_port_register(_vga_reg_port_external_fc);
        // Tell VGA controller to load palette register and lock any change to register
        struct VGAAttributeControllerIndexData load_palette_index = {
            .attribute_address      = 0,
            .palette_address_source = 1,
        };
        vga_set_single_port_register(_vga_reg_port_attribute_controller, register_const_serialize(&load_palette_index));
    }
}