#include "lib-header/driver/vga/register/attribute-controller.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Attribute controller registers - Unindexed
const struct VGARegisterPort _vga_reg_port_attribute_controller = {
    .data_register    = 0x3C0,
};

// Datas
const struct VGAAttributeControllerIndexData                  _vga_reg_mode13h_index_array[ATTRIBUTE_CONTROLLER_REGISTER_COUNT];
const struct VGAAttributeControllerPaletteData                _vga_reg_mode13h_palette_array[ATTRIBUTE_CONTROLLER_PALETTE_COUNT];

const struct VGAAttributeControllerAttributeModeControlData   _vga_reg_mode13h_attribute_mode_control;
const struct VGAAttributeControllerOverscanColorData          _vga_reg_mode13h_overscan_color;
const struct VGAAttributeControllerColorPlaneEnableData       _vga_reg_mode13h_color_plane_enable;
const struct VGAAttributeControllerHorizontalPixelPanningData _vga_reg_mode13h_horizontal_pixel_panning;
const struct VGAAttributeControllerColorSelectData            _vga_reg_mode13h_color_select;


void vga_set_attribute_controller_register(void) {
    uint8_t attribute_controller_index[21] = {
        
    };

    uint8_t attribute_controller_data[21] = {
        
    };

    // Read external register 0x3DA to force attribute controller switch into index state
    vga_read_unindexed_register(_vga_reg_port_external_fc);

    for (uint32_t i = 0; i < 21; i++) {
        vga_read_unindexed_register(_vga_reg_port_attribute_controller);
        // Send index first then data on exact same port
        vga_set_unindexed_register(_vga_reg_port_attribute_controller, attribute_controller_index[i]);
        vga_set_unindexed_register(_vga_reg_port_attribute_controller, attribute_controller_data[i]);
    }
    
}