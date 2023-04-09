#ifndef _VGA_CRT_CONTROLLER_REGISTER_H
#define _VGA_CRT_CONTROLLER_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"

// Mono use 0x3B4-0x3B5 instead
// Constant & indices
#define CRT_CONTROLLER_REGISTER_COUNT                  25

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

struct VGACRTControllerRegister {
    struct VGACRTControllerHorizontalTotalData         horizontal_total;
    struct VGACRTControllerEndHorizontalDisplayData    end_horizontal_display;
    struct VGACRTControllerStartHorizontalBlankingData start_horizontal_blanking;
    struct VGACRTControllerEndHorizontalBlankingData   end_horizontal_blanking;
    struct VGACRTControllerStartHorizontalRetraceData  start_horizontal_retrace;

    struct VGACRTControllerEndHorizontalRetraceData    end_horizontal_retrace;
    struct VGACRTControllerVerticalTotalData           vertical_total;
    struct VGACRTControllerOverflowData                overflow;
    struct VGACRTControllerPresetRowScanData           preset_row_scan;
    struct VGACRTControllerMaximumScanlineData         maximum_scanline;

    struct VGACRTControllerCursorStartData             cursor_start;
    struct VGACRTControllerCursorEndData               cursor_end;
    struct VGACRTControllerStartAddressHighData        start_address_high;
    struct VGACRTControllerStartAddressLowData         start_address_low;
    struct VGACRTControllerCursorLocationHighData      cursor_location_high;

    struct VGACRTControllerCursorLocationLowData       cursor_location_low;
    struct VGACRTControllerVerticalRetraceStartData    vertical_retrace_start;
    struct VGACRTControllerVerticalRetraceEndData      vertical_retrace_end;
    struct VGACRTControllerVerticalDisplayEndData      vertical_display_end;
    struct VGACRTControllerOffsetData                  offset;

    struct VGACRTControllerUnderlineLocationData       underline_location;
    struct VGACRTControllerStartVerticalBlankingData   start_vertical_blanking;
    struct VGACRTControllerEndVerticalBlankingData     end_vertical_blanking;
    struct VGACRTControllerCRTCModeControlData         ctrc_mode_control;
    struct VGACRTControllerLineCompareData             line_compare;
} __attribute__((packed));



extern const struct VGARegisterPort                             _vga_reg_port_crt_controller;



void vga_set_crt_controller_register(const struct VGACRTControllerRegister *crt_controller);

#endif