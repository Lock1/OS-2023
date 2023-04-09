#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/vga-register-programmer.h"

// Mono use 0x3B4-0x3B5 instead
const struct VGARegisterPort _vga_reg_port_crt_controller = {
    .address_register = 0x3D4,
    .data_register    = 0x3D5,
};



void vga_set_crt_controller_register(const struct VGACRTControllerRegister *crt_controller) {
    uint8_t crt_controller_index[CRT_CONTROLLER_REGISTER_COUNT] = {
        CRT_CONTROLLER_INDEX_HORIZONTAL_TOTAL,
        CRT_CONTROLLER_INDEX_END_HORIZONTAL_DISPLAY,
        CRT_CONTROLLER_INDEX_START_HORIZONTAL_BLANKING,
        CRT_CONTROLLER_INDEX_END_HORIZONTAL_BLANKING,
        CRT_CONTROLLER_INDEX_START_HORIZONTAL_RETRACE,

        CRT_CONTROLLER_INDEX_END_HORIZONTAL_RETRACE,
        CRT_CONTROLLER_INDEX_VERTICAL_TOTAL,
        CRT_CONTROLLER_INDEX_OVERFLOW,
        CRT_CONTROLLER_INDEX_PRESET_ROW_SCAN,
        CRT_CONTROLLER_INDEX_MAXIMUM_SCANLINE,

        CRT_CONTROLLER_INDEX_CURSOR_START,
        CRT_CONTROLLER_INDEX_CURSOR_END,
        CRT_CONTROLLER_INDEX_START_ADDRESS_HIGH,
        CRT_CONTROLLER_INDEX_START_ADDRESS_LOW,
        CRT_CONTROLLER_INDEX_CURSOR_LOCATION_HIGH,

        CRT_CONTROLLER_INDEX_CURSOR_LOCATION_LOW,
        CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_START,
        CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_END,
        CRT_CONTROLLER_INDEX_VERTICAL_DISPLAY_END,
        CRT_CONTROLLER_INDEX_OFFSET,

        CRT_CONTROLLER_INDEX_UNDERLINE_LOCATION,
        CRT_CONTROLLER_INDEX_START_VERTICAL_BLANKING,
        CRT_CONTROLLER_INDEX_END_VERTICAL_BLANKING,
        CRT_CONTROLLER_INDEX_CRTC_MODE_CONTROL,
        CRT_CONTROLLER_INDEX_LINE_COMPARE,
    };
    uint8_t crt_controller_data[CRT_CONTROLLER_REGISTER_COUNT] = {
        register_const_serialize(&crt_controller->horizontal_total),
        register_const_serialize(&crt_controller->end_horizontal_display),
        register_const_serialize(&crt_controller->start_horizontal_blanking),
        register_const_serialize(&crt_controller->end_horizontal_blanking),
        register_const_serialize(&crt_controller->start_horizontal_retrace),

        register_const_serialize(&crt_controller->end_horizontal_retrace),
        register_const_serialize(&crt_controller->vertical_total),
        register_const_serialize(&crt_controller->overflow),
        register_const_serialize(&crt_controller->preset_row_scan),
        register_const_serialize(&crt_controller->maximum_scanline),

        register_const_serialize(&crt_controller->cursor_start),
        register_const_serialize(&crt_controller->cursor_end),
        register_const_serialize(&crt_controller->start_address_high),
        register_const_serialize(&crt_controller->start_address_low),
        register_const_serialize(&crt_controller->cursor_location_high),
        
        register_const_serialize(&crt_controller->cursor_location_low),
        register_const_serialize(&crt_controller->vertical_retrace_start),
        register_const_serialize(&crt_controller->vertical_retrace_end),
        register_const_serialize(&crt_controller->vertical_display_end),
        register_const_serialize(&crt_controller->offset),

        register_const_serialize(&crt_controller->underline_location),
        register_const_serialize(&crt_controller->start_vertical_blanking),
        register_const_serialize(&crt_controller->end_vertical_blanking),
        register_const_serialize(&crt_controller->ctrc_mode_control),
        register_const_serialize(&crt_controller->line_compare),
    };

    // Not sure why it need to be set first
    vga_set_double_port_register(_vga_reg_port_crt_controller, CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_END, 0x0E);

    set_indexed_register(_vga_reg_port_crt_controller, crt_controller_index, crt_controller_data, CRT_CONTROLLER_REGISTER_COUNT);
}