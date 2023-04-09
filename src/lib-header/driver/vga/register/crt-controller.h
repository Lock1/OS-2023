#ifndef _VGA_CRT_CONTROLLER_REGISTER_H
#define _VGA_CRT_CONTROLLER_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"

// Indexes
#define CRT_CONTROLLER_INDEX_HORIZONTAL_TOTAL          0x0
#define CRT_CONTROLLER_INDEX_END_HORIZONTAL_DISPLAY    0x1
#define CRT_CONTROLLER_INDEX_START_HORIZONTAL_BLANKING 0x2
#define CRT_CONTROLLER_INDEX_END_HORIZONTAL_BLANKING   0x3
#define CRT_CONTROLLER_INDEX_START_HORIZONTAL_RETRACE  0x4
#define CRT_CONTROLLER_INDEX_END_HORIZONTAL_RETRACE    0x5
#define CRT_CONTROLLER_INDEX_VERTICAL_TOTAL            0x6
#define CRT_CONTROLLER_INDEX_OVERFLOW                  0x7
#define CRT_CONTROLLER_INDEX_PRESET_ROW_SCAN           0x8
#define CRT_CONTROLLER_INDEX_MAXIMUM_SCANLINE          0x9
#define CRT_CONTROLLER_INDEX_CURSOR_START              0xA
#define CRT_CONTROLLER_INDEX_CURSOR_END                0xB
#define CRT_CONTROLLER_INDEX_START_ADDRESS_HIGH        0xC
#define CRT_CONTROLLER_INDEX_START_ADDRESS_LOW         0xD
#define CRT_CONTROLLER_INDEX_CURSOR_LOCATION_HIGH      0xE
#define CRT_CONTROLLER_INDEX_CURSOR_LOCATION_LOW       0xF
#define CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_START    0x10
#define CRT_CONTROLLER_INDEX_VERTICAL_RETRACE_END      0x11
#define CRT_CONTROLLER_INDEX_VERTICAL_DISPLAY_END      0x12
#define CRT_CONTROLLER_INDEX_OFFSET                    0x13
#define CRT_CONTROLLER_INDEX_UNDERLINE_LOCATION        0x14
#define CRT_CONTROLLER_INDEX_START_VERTICAL_BLANKING   0x15
#define CRT_CONTROLLER_INDEX_END_VERTICAL_BLANKING     0x16
#define CRT_CONTROLLER_INDEX_CRTC_MODE_CONTROL         0x17
#define CRT_CONTROLLER_INDEX_LINE_COMPARE              0x18



// Register datas
struct VGACRTControllerHorizontalTotalData {
    uint8_t horizontal_total;
} __attribute__((packed));

struct VGACRTControllerEndHorizontalDisplayData {
    uint8_t end_horizontal_display;
} __attribute__((packed));

struct VGACRTControllerStartHorizontalBlankingData {
    uint8_t start_horizontal_blanking;
} __attribute__((packed));

struct VGACRTControllerEndHorizontalBlankingData {
    uint8_t end_horizontal_blanking: 5;
    uint8_t display_enable_skew:     2;
    uint8_t vertical_rectrace:       1;
} __attribute__((packed));

struct VGACRTControllerStartHorizontalRetraceData {
    uint8_t start_horizontal_retrace;
} __attribute__((packed));

struct VGACRTControllerEndHorizontalRetraceData {
    uint8_t end_horizontal_retrace:    5;
    uint8_t horizontal_retrace_skew:   2;
    uint8_t end_horizontal_blanking_5: 1;
} __attribute__((packed));

struct VGACRTControllerVerticalTotalData {
    uint8_t vertical_total;
} __attribute__((packed));

struct VGACRTControllerOverflowData {
    uint8_t vertical_total_8:          1;
    uint8_t vertical_display_end_8:    1;
    uint8_t vertical_retrace_start_8:  1;
    uint8_t start_vertical_blanking_8: 1;
    uint8_t line_compare_8:            1;
    uint8_t vertical_total_9:          1;
    uint8_t vertical_display_end_9:    1;
    uint8_t vertical_retrace_start_9:  1;
} __attribute__((packed));

struct VGACRTControllerPresetRowScanData {
    uint8_t preset_row_scan: 5;
    uint8_t byte_panning:    2;
    uint8_t _reserved:       1;
} __attribute__((packed));

struct VGACRTControllerMaximumScanlineData {
    uint8_t maximum_scanline:          5;
    uint8_t start_vertical_blanking_9: 1;
    uint8_t line_compare_9:            1;
    uint8_t scan_doubling:             1;
} __attribute__((packed));

struct VGACRTControllerCursorStartData {
    uint8_t cursor_scanline_start: 5;
    uint8_t cursor_disable:        1;
    uint8_t _reserved:             2;
} __attribute__((packed));

struct VGACRTControllerCursorEndData {
    uint8_t cursor_scanline_end: 5;
    uint8_t ega_cursor_skew:     2;
    uint8_t _reserved:           1;
} __attribute__((packed));

struct VGACRTControllerStartAddressHighData {
    uint8_t start_address_high;
} __attribute__((packed));

struct VGACRTControllerStartAddressLowData {
    uint8_t start_address_low;
} __attribute__((packed));

struct VGACRTControllerCursorLocationHighData {
    uint8_t cursor_location_high;
} __attribute__((packed));

struct VGACRTControllerCursorLocationLowData {
    uint8_t cursor_location_low;
} __attribute__((packed));

struct VGACRTControllerVerticalRetraceStartData {
    uint8_t vertical_retrace_start;
} __attribute__((packed));

struct VGACRTControllerVerticalRetraceEndData {
    uint8_t vertical_retrace_end: 4;
    uint8_t _reserved:            2;
    uint8_t memory_bandwidth:     1;
    uint8_t protect_crt_register: 1;
} __attribute__((packed));

struct VGACRTControllerVerticalDisplayEndData {
    uint8_t vertical_display_end;
} __attribute__((packed));

struct VGACRTControllerOffsetData {
    uint8_t offset;
} __attribute__((packed));

struct VGACRTControllerUnderlineLocationData {
    uint8_t underline_location:     5;
    uint8_t divide_4_address_clock: 1;
    uint8_t double_word_addressing: 1;
    uint8_t _reserved:              1;
} __attribute__((packed));

struct VGACRTControllerStartVerticalBlankingData {
    uint8_t start_vertical_blanking;
} __attribute__((packed));

// Note: OSDever said this 7-bit, but asmhacker said 8-bit
struct VGACRTControllerEndVerticalBlankingData {
    uint8_t end_vertical_blanking;
} __attribute__((packed));

struct VGACRTControllerCRTCModeControlData {
    uint8_t map_display_address_13: 1;
    uint8_t map_display_address_14: 1;
    uint8_t divide_2_scanline:      1;
    uint8_t divide_2_address_clock: 1;
    uint8_t _reserved:              1;
    uint8_t address_wrap:           1;
    uint8_t use_byte_mode:          1;
    uint8_t sync_enable:            1;
} __attribute__((packed));

struct VGACRTControllerLineCompareData {
    uint8_t line_compare_register;
} __attribute__((packed));


// VGA register port
extern const struct VGARegisterPort                             _vga_reg_port_crt_controller;

// Video Mode 13h values
extern const struct VGACRTControllerHorizontalTotalData         _vga_reg_mode_13h_horizontal_total;
extern const struct VGACRTControllerEndHorizontalDisplayData    _vga_reg_mode_13h_end_horizontal_display;
extern const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode_13h_start_horizontal_blanking;
extern const struct VGACRTControllerEndHorizontalBlankingData   _vga_reg_mode_13h_end_horizontal_blanking;
extern const struct VGACRTControllerStartHorizontalRetraceData  _vga_reg_mode_13h_start_horizontal_retrace;

extern const struct VGACRTControllerEndHorizontalRetraceData    _vga_reg_mode_13h_end_horizontal_retrace;
extern const struct VGACRTControllerVerticalTotalData           _vga_reg_mode_13h_vertical_total;
extern const struct VGACRTControllerOverflowData                _vga_reg_mode_13h_overflow;
extern const struct VGACRTControllerPresetRowScanData           _vga_reg_mode_13h_preset_row_scan;
extern const struct VGACRTControllerMaximumScanlineData         _vga_reg_mode_13h_maximum_scanline;

extern const struct VGACRTControllerCursorStartData             _vga_reg_mode_13h_cursor_start;
extern const struct VGACRTControllerCursorEndData               _vga_reg_mode_13h_cursor_end;
extern const struct VGACRTControllerStartAddressHighData        _vga_reg_mode_13h_start_address_high;
extern const struct VGACRTControllerStartAddressLowData         _vga_reg_mode_13h_start_address_low;
extern const struct VGACRTControllerCursorLocationHighData      _vga_reg_mode_13h_cursor_location_high;

extern const struct VGACRTControllerCursorLocationLowData       _vga_reg_mode_13h_cursor_location_low;
extern const struct VGACRTControllerVerticalRetraceStartData    _vga_reg_mode_13h_vertical_retrace_start;
extern const struct VGACRTControllerVerticalRetraceEndData      _vga_reg_mode_13h_vertical_retrace_end;
extern const struct VGACRTControllerVerticalDisplayEndData      _vga_reg_mode_13h_vertical_display_end;
extern const struct VGACRTControllerOffsetData                  _vga_reg_mode_13h_offset;

extern const struct VGACRTControllerUnderlineLocationData       _vga_reg_mode_13h_underline_location;
extern const struct VGACRTControllerStartVerticalBlankingData   _vga_reg_mode_13h_start_vertical_blanking;
extern const struct VGACRTControllerEndVerticalBlankingData     _vga_reg_mode_13h_end_vertical_blanking;
extern const struct VGACRTControllerCRTCModeControlData         _vga_reg_mode_13h_ctrc_mode_control;
extern const struct VGACRTControllerLineCompareData             _vga_reg_mode_13h_line_compare;

void vga_set_mode_13h_crt_controller_register(void);

#endif