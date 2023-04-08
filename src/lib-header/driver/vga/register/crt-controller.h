#ifndef _VGA_CRT_CONTROLLER_REGISTER_H
#define _VGA_CRT_CONTROLLER_REGISTER_H

#include "lib-header/driver/vga/vga-register.h"
#include "lib-header/stdtype.h"

// Indexes
#define CRT_INDEX_HORIZONTAL_TOTAL          0x0
#define CRT_INDEX_END_HORIZONTAL_DISPLAY    0x1
#define CRT_INDEX_START_HORIZONTAL_BLANKING 0x2
#define CRT_INDEX_END_HORIZONTAL_BLANKING   0x3
#define CRT_INDEX_START_HORIZONTAL_RETRACE  0x4
#define CRT_INDEX_END_HORIZONTAL_RETRACE    0x5
#define CRT_INDEX_VERTICAL_TOTAL            0x6
#define CRT_INDEX_OVERFLOW                  0x7
#define CRT_INDEX_PRESET_ROW_SCAN           0x8
#define CRT_INDEX_MAXIMUM_SCANLINE          0x9
#define CRT_INDEX_CURSOR_START              0xA
#define CRT_INDEX_CURSOR_END                0xB
#define CRT_INDEX_START_ADDRESS_HIGH        0xC
#define CRT_INDEX_START_ADDRESS_LOW         0xD
#define CRT_INDEX_CURSOR_LOCATION_HIGH      0xE
#define CRT_INDEX_CURSOR_LOCATION_LOW       0xF
#define CRT_INDEX_VERTICAL_RETRACE_START    0x10
#define CRT_INDEX_VERTICAL_RETRACE_END      0x11
#define CRT_INDEX_VERTICAL_DISPLAY_END      0x12
#define CRT_INDEX_OFFSET                    0x13
#define CRT_INDEX_UNDERLINE_LOCATION        0x14
#define CRT_INDEX_START_VERTICAL_BLANKING   0x15
#define CRT_INDEX_END_VERTICAL_BLANKING     0x16
#define CRT_INDEX_CRTC_MODE_CONTROL         0x17
#define CRT_INDEX_LINE_COMPARE              0x18



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



// VGA register port
extern const struct VGARegisterPort              _vga_reg_sequencer;

// Video Mode 13h values
extern const struct VGACRTControllerHorizontalTotalData         _vga_reg_mode13h_horizontal_total;
extern const struct VGACRTControllerEndHorizontalDisplayData    _vga_reg_mode13h_end_horizontal_display;
extern const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking;
extern const struct VGACRTControllerEndHorizontalBlankingData   _vga_reg_mode13h_end_horizontal_blanking;

void vga_set_crt_controller_register(void);

#endif