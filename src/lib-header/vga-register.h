#ifndef _VGA_REGISTER_H
#define _VGA_REGISTER_H

#include "lib-header/stdtype.h"

// Note : Naming convention directly follow from http://www.osdever.net/FreeVGA/vga/vga.htm

#define SEQUENCER_INDEX_RESET         0
#define SEQUENCER_INDEX_CLOCKING_MODE 1
#define SEQUENCER_INDEX_MAP_MASK      2
#define SEQUENCER_INDEX_CHARACTER_MAP 3
#define SEQUENCER_INDEX_MEMORY_MODE   4

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

// TODO : Even more abstraction, split register struct into few file

struct VGARegisterPort {
    uint16_t   address_register;
    uint16_t   data_register;
} __attribute__((packed));





// VGA Register values, avoiding raw bytes and use struct as much as possible, even if somewhat feel stupid
// Sequencer
struct VGASequencerResetData {
    uint8_t asynchronous_reset: 1;
    uint8_t synchronous_reset:  1;
    uint8_t _reserved:          6;
} __attribute__((packed));

struct VGASequencerClockingModeData {
    uint8_t dot_9_8_mode:    1;
    uint8_t _reserved_1:     1;
    uint8_t shift_load_rate: 1;
    uint8_t dot_clock_rate:  1;
    uint8_t shift_four_mode: 1;
    uint8_t screen_disable:  1;
    uint8_t _reserved_2:     2;
} __attribute__((packed));

struct VGASequencerMapMaskData {
    uint8_t enable_memory_plane_0: 1;
    uint8_t enable_memory_plane_1: 1;
    uint8_t enable_memory_plane_2: 1;
    uint8_t enable_memory_plane_3: 1;
    uint8_t _reserved:             4;
} __attribute__((packed));

struct VGASequencerCharacterMapData {
    uint8_t character_set_b:      2;
    uint8_t character_set_a:      2;
    uint8_t second_bit_charset_b: 1;
    uint8_t second_bit_charset_a: 1;
    uint8_t _reserved:            2;
} __attribute__((packed));

struct VGASequencerMemoryModeData {
    uint8_t _reserved_1:             1;
    uint8_t extended_memory:         1;
    uint8_t disable_odd_even_memory: 1;
    uint8_t enable_chain_four:       1;
    uint8_t _reserved_2:             4;
} __attribute__((packed));


// CRT Controller
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

// External Registers
struct VGAExternalOutputRegisterData {
    uint8_t ioas:            1;
    uint8_t ram_enable:      1;
    uint8_t clock_select:    2;
    uint8_t _reserved:       1;
    uint8_t odd_even_page:   1;
    uint8_t horizontal_sync: 1;
    uint8_t vertical_sync:   1;
} __attribute__((packed));

struct VGAExternalFeatureControlData {
    uint8_t feature_control0: 1;
    uint8_t feature_control1: 1;
    uint8_t _reserved:        6;
} __attribute__((packed));






// VGA register port
extern const struct VGARegisterPort _vga_reg_sequencer;
extern const struct VGARegisterPort _vga_reg_crt_controller;

// External / Misc registers, http://www.osdever.net/FreeVGA/vga/extreg.htm
extern const struct VGARegisterPort _vga_reg_external_output;
extern const struct VGARegisterPort _vga_reg_external_fc;

// Video Mode 13h values
// Sequencer register count : 5
extern const struct VGASequencerResetData        _vga_reg_mode13h_reset;
extern const struct VGASequencerClockingModeData _vga_reg_mode13h_clocking_mode;
extern const struct VGASequencerMapMaskData      _vga_reg_mode13h_map_mask;
extern const struct VGASequencerCharacterMapData _vga_reg_mode13h_character_map;
extern const struct VGASequencerMemoryModeData   _vga_reg_mode13h_sequencer_memory_mode;

// CRT Controller register count : 25
extern const struct VGACRTControllerHorizontalTotalData         _vga_reg_mode13h_horizontal_total;
extern const struct VGACRTControllerEndHorizontalDisplayData    _vga_reg_mode13h_end_horizontal_display;
extern const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking;
extern const struct VGACRTControllerEndHorizontalBlankingData   _vga_reg_mode13h_end_horizontal_blanking;

extern const struct VGAExternalOutputRegisterData _vga_reg_mode13h_output;
extern const struct VGAExternalFeatureControlData _vga_reg_mode13h_fc;


#endif