#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/vga-register.h"

// Mono use 0x3B4-0x3B5 instead
const struct VGARegisterPort _vga_reg_port_crt_controller = {
    .address_register = 0x3D4,
    .data_register    = 0x3D5,
};

// CRT Controller values
const struct VGACRTControllerHorizontalTotalData         _vga_reg_mode13h_horizontal_total = {
    .horizontal_total = 0x5F,
};

const struct VGACRTControllerEndHorizontalDisplayData    _vga_reg_mode13h_end_horizontal_display = {
    .end_horizontal_display = 0x4F,
};

const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking = {
    .start_horizontal_blanking = 0x50,
};

const struct VGACRTControllerEndHorizontalBlankingData   _vga_reg_mode13h_end_horizontal_blanking = {
    .end_horizontal_blanking = 0b00010,
    .display_enable_skew     = 0,
    .vertical_rectrace       = 1,
};

const struct VGACRTControllerStartHorizontalRetraceData  _vga_reg_mode13h_start_horizontal_retrace = {
    .start_horizontal_retrace = 0x54,
};



const struct VGACRTControllerEndHorizontalRetraceData    _vga_reg_mode13h_end_horizontal_retrace = {
    .end_horizontal_retrace    = 0,
    .horizontal_retrace_skew   = 0,
    .end_horizontal_blanking_5 = 1,
};

const struct VGACRTControllerVerticalTotalData           _vga_reg_mode13h_vertical_total = {
    .vertical_total = 0xBF,
};

const struct VGACRTControllerOverflowData                _vga_reg_mode13h_overflow = {
    .vertical_total_8          = 1,
    .vertical_display_end_8    = 1,
    .vertical_retrace_start_8  = 1,
    .start_vertical_blanking_8 = 1,
    .line_compare_8            = 1,
    .vertical_total_9          = 0,
    .vertical_display_end_9    = 0,
    .vertical_retrace_start_9  = 0,
};

const struct VGACRTControllerPresetRowScanData           _vga_reg_mode13h_preset_row_scan = {
    .byte_panning    = 0,
    .preset_row_scan = 0,
};

const struct VGACRTControllerMaximumScanlineData         _vga_reg_mode13h_maximum_scanline = {
    .maximum_scanline          = 0b00001,
    .start_vertical_blanking_9 = 0,
    .line_compare_9            = 1,
    .scan_doubling             = 0,
};



const struct VGACRTControllerCursorStartData             _vga_reg_mode13h_cursor_start = {
    .cursor_scanline_start = 0,
    .cursor_disable        = 0,
};

const struct VGACRTControllerCursorEndData               _vga_reg_mode13h_cursor_end = {
    .cursor_scanline_end = 0,
    .ega_cursor_skew     = 0,
};

const struct VGACRTControllerStartAddressHighData        _vga_reg_mode13h_start_address_high = {
    .start_address_high = 0,
};

const struct VGACRTControllerStartAddressLowData         _vga_reg_mode13h_start_address_low = {
    .start_address_low = 0,
};

const struct VGACRTControllerCursorLocationHighData      _vga_reg_mode13h_cursor_location_high = {
    .cursor_location_high = 0,
};



const struct VGACRTControllerCursorLocationLowData       _vga_reg_mode13h_cursor_location_low = {
    .cursor_location_low = 0,
};

const struct VGACRTControllerVerticalRetraceStartData    _vga_reg_mode13h_vertical_retrace_start = {
    .vertical_retrace_start = 0x9C,
};

const struct VGACRTControllerVerticalRetraceEndData      _vga_reg_mode13h_vertical_retrace_end = {
    .vertical_retrace_end = 0xE,
    .memory_bandwidth     = 0,
    .protect_crt_register = 0,
};

const struct VGACRTControllerVerticalDisplayEndData      _vga_reg_mode13h_vertical_display_end = {
    .vertical_display_end = 0x8F,
};

const struct VGACRTControllerOffsetData                  _vga_reg_mode13h_offset = {
    .offset = 0x28,
};



const struct VGACRTControllerUnderlineLocationData       _vga_reg_mode13h_underline_location = {
    .underline_location     = 0,
    .divide_4_address_clock = 0,
    .double_word_addressing = 1,
};

const struct VGACRTControllerStartVerticalBlankingData   _vga_reg_mode13h_start_vertical_blanking = {
    .start_vertical_blanking = 0x96,
};

const struct VGACRTControllerEndVerticalBlankingData     _vga_reg_mode13h_end_vertical_blanking = {
    .end_vertical_blanking = 0xB9,
};

const struct VGACRTControllerCRTCModeControlData         _vga_reg_mode13h_ctrc_mode_control = {
    .map_display_address_13 = 1,
    .map_display_address_14 = 1,
    .divide_2_scanline      = 0,
    .divide_2_address_clock = 0,
    .address_wrap           = 1,
    .use_byte_mode          = 0,
    .sync_enable            = 1,
};

const struct VGACRTControllerLineCompareData             _vga_reg_mode13h_line_compare = {
    .line_compare_register = 0xFF,
};




void vga_set_crt_controller_register(void) {
    uint8_t crt_controller_index[25] = {
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
    uint8_t crt_controller_data[25] = {
        register_const_serialize(&_vga_reg_mode13h_horizontal_total),
        register_const_serialize(&_vga_reg_mode13h_end_horizontal_display),
        register_const_serialize(&_vga_reg_mode13h_start_horizontal_blanking),
        register_const_serialize(&_vga_reg_mode13h_end_horizontal_blanking),
        register_const_serialize(&_vga_reg_mode13h_start_horizontal_retrace),

        register_const_serialize(&_vga_reg_mode13h_end_horizontal_retrace),
        register_const_serialize(&_vga_reg_mode13h_vertical_total),
        register_const_serialize(&_vga_reg_mode13h_overflow),
        register_const_serialize(&_vga_reg_mode13h_preset_row_scan),
        register_const_serialize(&_vga_reg_mode13h_maximum_scanline),

        register_const_serialize(&_vga_reg_mode13h_cursor_start),
        register_const_serialize(&_vga_reg_mode13h_cursor_end),
        register_const_serialize(&_vga_reg_mode13h_start_address_high),
        register_const_serialize(&_vga_reg_mode13h_start_address_low),
        register_const_serialize(&_vga_reg_mode13h_cursor_location_high),
        
        register_const_serialize(&_vga_reg_mode13h_cursor_location_low),
        register_const_serialize(&_vga_reg_mode13h_vertical_retrace_start),
        register_const_serialize(&_vga_reg_mode13h_vertical_retrace_end),
        register_const_serialize(&_vga_reg_mode13h_vertical_display_end),
        register_const_serialize(&_vga_reg_mode13h_offset),

        register_const_serialize(&_vga_reg_mode13h_underline_location),
        register_const_serialize(&_vga_reg_mode13h_start_vertical_blanking),
        register_const_serialize(&_vga_reg_mode13h_end_vertical_blanking),
        register_const_serialize(&_vga_reg_mode13h_ctrc_mode_control),
        register_const_serialize(&_vga_reg_mode13h_line_compare),
    };

    // TODO : Need to check whether my interpretation of out16(0x0E11) is correct
    vga_set_index_register(_vga_reg_port_crt_controller, CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_END, 0x0E);

    set_indexed_register(_vga_reg_port_crt_controller, crt_controller_index, crt_controller_data, 4);
}