#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/vga-register.h"

// Mono use 0x3B4-0x3B5 instead
const struct VGARegisterPort _vga_reg_crt_controller = {
    .address_register = 0x3D4,
    .data_register    = 0x3D5,
};


// FIXME : CRT Controller
const struct VGACRTControllerHorizontalTotalData _vga_reg_mode13h_horizontal_total = {
    .horizontal_total = 3,
};

const struct VGACRTControllerEndHorizontalDisplayData _vga_reg_mode13h_end_horizontal_display = {
    .end_horizontal_display = 0,
};

const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking = {
    .start_horizontal_blanking = 3,
};

const struct VGACRTControllerEndHorizontalBlankingData _vga_reg_mode13h_end_horizontal_blanking = {
    .end_horizontal_blanking = 0,
    .display_enable_skew     = 0,
    .vertical_rectrace       = 0,
};



void vga_set_crt_controller_register(void) {
    uint8_t crt_controller_index[25] = {
        CRT_INDEX_HORIZONTAL_TOTAL,
        CRT_INDEX_END_HORIZONTAL_DISPLAY,
        CRT_INDEX_START_HORIZONTAL_BLANKING,
        CRT_INDEX_END_HORIZONTAL_BLANKING,
    };
    uint8_t crt_controller_data[25] = {
        register_const_serialize(&_vga_reg_mode13h_horizontal_total),
        register_const_serialize(&_vga_reg_mode13h_end_horizontal_display),
        register_const_serialize(&_vga_reg_mode13h_start_horizontal_blanking),
        register_const_serialize(&_vga_reg_mode13h_end_horizontal_blanking),
    };
    set_indexed_register(_vga_reg_crt_controller, crt_controller_index, crt_controller_data, 4);
}