#include "lib-header/driver/vga/video-mode-preset/mode-13h.h"

const struct VGAExternalRegister _vga_preset_mode_13h_external = {
    .output          = {
        .ioas             = 1,
        .ram_enable       = 1,
        .clock_select     = 0,
        .odd_even_page    = 1,
        .horizontal_sync  = 1,
        .vertical_sync    = 0,
    },
    .feature_control = {
        .feature_control0 = 0,
        .feature_control1 = 0,
    },
};



const struct VGASequencerRegister _vga_preset_mode_13h_sequencer = {
    .reset = {
        .asynchronous_reset      = 1,
        .synchronous_reset       = 1,
    },
    .clocking_mode = {
        .dot_9_8_mode            = 1,
        .shift_load_rate         = 0,
        .dot_clock_rate          = 0,
        .shift_four_mode         = 0,
        .screen_disable          = 0,
    },
    .map_mask = {
        .enable_memory_plane_0   = 1,
        .enable_memory_plane_1   = 1,
        .enable_memory_plane_2   = 1,
        .enable_memory_plane_3   = 1,
    },
    .character_map = {
        .character_set_b         = 0,
        .character_set_a         = 0,
        .second_bit_charset_b    = 0,
        .second_bit_charset_a    = 0,
    },
    .sequencer_memory_mode = {
        .extended_memory         = 1,
        .disable_odd_even_memory = 1,
        .enable_chain_four       = 1,
    },
};



const struct VGACRTControllerRegister _vga_preset_mode_13h_crt_controller = {
    .horizontal_total = {
        .horizontal_total          = 0x5F,
    },
    .end_horizontal_display = {
        .end_horizontal_display    = 0x4F,
    },
    .start_horizontal_blanking = {
        .start_horizontal_blanking = 0x50,
    },
    .end_horizontal_blanking = {
        .end_horizontal_blanking   = 0b00010,
        .display_enable_skew       = 0,
        .vertical_rectrace         = 1,
    },
    .start_horizontal_retrace = {
        .start_horizontal_retrace  = 0x54,
    },

    .end_horizontal_retrace = {
        .end_horizontal_retrace    = 0,
        .horizontal_retrace_skew   = 0,
        .end_horizontal_blanking_5 = 1,
    },
    .vertical_total = {
        .vertical_total = 0xBF,
    },
    .overflow = {
        .vertical_total_8          = 1,
        .vertical_display_end_8    = 1,
        .vertical_retrace_start_8  = 1,
        .start_vertical_blanking_8 = 1,
        .line_compare_8            = 1,
        .vertical_total_9          = 0,
        .vertical_display_end_9    = 0,
        .vertical_retrace_start_9  = 0,
    },
    .preset_row_scan = {
        .byte_panning              = 0,
        .preset_row_scan           = 0,
    },
    .maximum_scanline = {
        .maximum_scanline          = 0b00001,
        .start_vertical_blanking_9 = 0,
        .line_compare_9            = 1,
        .scan_doubling             = 0,
    },

    .cursor_start = {
        .cursor_scanline_start     = 0,
        .cursor_disable            = 0,
    },
    .cursor_end = {
        .cursor_scanline_end       = 0,
        .ega_cursor_skew           = 0,
    },
    .start_address_high = {
        .start_address_high        = 0,
    },
    .start_address_low = {
        .start_address_low         = 0,
    },
    .cursor_location_high = {
        .cursor_location_high      = 0,
    },

    .cursor_location_low = {
        .cursor_location_low       = 0,
    },
    .vertical_retrace_start = {
        .vertical_retrace_start    = 0x9C,
    },
    .vertical_retrace_end = {
        .vertical_retrace_end      = 0xE,
        .memory_bandwidth          = 0,
        .protect_crt_register      = 0,
    },
    .vertical_display_end = {
        .vertical_display_end      = 0x8F,
    },
    .offset = {
        .offset                    = 0x28,
    },

    .underline_location = {
        .underline_location        = 0,
        .divide_4_address_clock    = 0,
        .double_word_addressing    = 1,
    },
    .start_vertical_blanking = {
        .start_vertical_blanking   = 0x96,
    },
    .end_vertical_blanking = {
        .end_vertical_blanking     = 0xB9,
    },
    .ctrc_mode_control = {
        .map_display_address_13    = 1,
        .map_display_address_14    = 1,
        .divide_2_scanline         = 0,
        .divide_2_address_clock    = 0,
        .address_wrap              = 1,
        .use_byte_mode             = 0,
        .sync_enable               = 1,
    },
    .line_compare = {
        .line_compare_register     = 0xFF,
    },
};



const struct VGAGraphicsRegister _vga_preset_mode_13h_graphics = {
    .set_reset = {
        .plane_0_set_reset        = 0,
        .plane_1_set_reset        = 0,
        .plane_2_set_reset        = 0,
        .plane_3_set_reset        = 0,
    },
    .enable_set_reset = {
        .plane_0_enable_set_reset = 0,
        .plane_1_enable_set_reset = 0,
        .plane_2_enable_set_reset = 0,
        .plane_3_enable_set_reset = 0,
    },
    .color_compare = {
        .plane_0_color_compare    = 0,
        .plane_1_color_compare    = 0,
        .plane_2_color_compare    = 0,
        .plane_3_color_compare    = 0,
    },
    .data_rotate = {
        .logical_operation        = 0,
        .rotate_count             = 0,
    },
    .read_map_select = {
        .read_map_select          = 0,
    },

    .graphics_mode = {
        .write_mode               = 0,
        .read_mode                = 0,
        .host_even_odd            = 0,
        .interleave_register      = 0,
        .color_shift_256          = 1,
    },
    .miscellaneous_graphics = {
        .alphanumeric_disable     = 1,
        .chain_even_odd           = 0,
        .memory_map_select        = 1,
    },
    .color_dont_care = {
        .plane_0_color_dont_care  = 1,
        .plane_1_color_dont_care  = 1,
        .plane_2_color_dont_care  = 1,
        .plane_3_color_dont_care  = 1,
    },
    .bit_mask = {
        .bit_mask                 = 0xFF,
    },
};



const struct VGAAttributeControllerRegister _vga_preset_mode_13h_attribute_controller = {
    .palette_array = {
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
    },
    .attribute_mode_control = {
        .attribute_controller_graphics_enable = 1,
        .monochrome_emulation                 = 0,
        .line_graphics                        = 0,
        .blink_enable                         = 0,
        .pixel_panning_mode                   = 0,
        .color_8_bit_mode                     = 1,
        .palette_bit_5_4                      = 0,
    },
    .overscan_color = {
        .overscan_palette_index               = 0,
    },
    .color_plane_enable = {
        .plane_0_color_plane_enable           = 1,
        .plane_1_color_plane_enable           = 1,
        .plane_2_color_plane_enable           = 1,
        .plane_3_color_plane_enable           = 1,
    },
    .horizontal_pixel_panning = {
        .pixel_shift_count                    = 0,
    },
    .color_select = {
        .color_select_5_4                     = 0,
        .color_select_7_6                     = 0,
    },
};



const uint8_t _vga_preset_mode_13h_color_palette[MODE_13H_COLOR*3] = {
    00, 00, 00, 00, 10, 41, 12, 28, 18,  2, 43, 22, 35, 19,  9, 58, 
    00, 00, 57, 35, 12, 43, 43, 47, 24, 24, 28, 20, 24, 60, 10, 60, 
    15, 31, 47, 63, 62, 56, 20, 60, 56, 22, 63, 61, 36, 63, 63, 63, 
    00, 00, 00,  5,  5,  5,  8,  8,  8, 11, 11, 11, 14, 14, 14, 17, 
    17, 17, 20, 20, 20, 24, 24, 24, 28, 28, 28, 32, 32, 32, 36, 36, 
    36, 40, 40, 40, 45, 45, 45, 50, 50, 50, 56, 56, 56, 63, 63, 63, 
    13, 12, 15, 15, 16, 22, 17, 20, 29, 19, 24, 36, 21, 28, 43, 23, 
    31, 50, 25, 34, 57, 26, 42, 63, 00, 15,  2,  1, 22,  4,  2, 29, 
     6,  3, 36,  8,  4, 43, 10,  5, 50, 12,  6, 57, 14, 20, 63, 40, 
    18,  6,  7, 25, 12, 11, 33, 17, 14, 40, 23, 18, 48, 28, 21, 55, 
    34, 25, 62, 39, 27, 63, 48, 36, 15,  3,  2, 22,  6,  4, 29,  9, 
     6, 36, 12,  8, 43, 15, 10, 50, 18, 12, 57, 21, 14, 63, 28, 20, 
    15, 00, 00, 22,  7, 00, 29, 15, 00, 36, 23, 00, 43, 31, 00, 50,
    39, 00, 57, 47, 00, 63, 55, 00, 15,  5,  3, 22, 11,  7, 29, 17, 
    11, 36, 23, 15, 43, 29, 19, 50, 35, 23, 57, 41, 27, 63, 53, 34, 
    28, 14, 12, 33, 20, 14, 38, 26, 16, 43, 32, 18, 48, 38, 20, 53, 
    44, 22, 58, 50, 24, 63, 56, 30,  5,  5,  6, 10, 10, 13, 15, 15, 
    20, 20, 20, 27, 25, 25, 34, 30, 30, 41, 35, 35, 48, 44, 44, 63, 
     3,  6,  5,  5, 11,  9,  7, 16, 13,  9, 21, 17, 11, 26, 21, 13, 
    31, 25, 15, 36, 29, 20, 48, 38,  6,  6,  7, 13, 13, 15, 20, 20, 
    23, 27, 27, 31, 34, 34, 39, 41, 41, 47, 48, 48, 55, 57, 57, 63, 
     6, 15,  4, 12, 22,  8, 18, 29, 12, 24, 36, 16, 30, 43, 20, 36, 
    50, 24, 42, 57, 28, 54, 63, 35, 15, 10, 10, 22, 16, 16, 29, 21, 
    21, 36, 27, 27, 43, 32, 32, 50, 38, 38, 57, 43, 43, 63, 54, 54, 
    15, 15,  6, 22, 22, 12, 29, 29, 18, 36, 36, 24, 43, 43, 30, 50, 
    50, 36, 57, 57, 42, 63, 63, 54,  2,  4, 14,  6, 12, 21, 10, 20,
    28, 14, 28, 35, 18, 36, 42, 22, 44, 49, 26, 52, 56, 36, 63, 63, 
    18,  4, 14, 24,  8, 21, 31, 12, 28, 37, 16, 35, 44, 20, 42, 50, 
    24, 49, 57, 28, 56, 63, 38, 63, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 53, 44, 22, 
     9,  8, 12, 16, 14, 16, 22, 21, 20, 29, 27, 24, 35, 34, 28, 42, 
    40, 32, 48, 47, 36, 57, 56, 43,  8, 12, 16, 14, 16, 22, 21, 20, 
    29, 27, 24, 35, 34, 28, 42, 40, 32, 48, 47, 36, 57, 56, 43, 63, 
    13, 9,  11, 21, 16, 15, 27, 22, 18, 36, 29, 22, 42, 35, 25, 51, 
    42, 29, 57, 48, 32, 63, 56, 39,  6, 14,  9, 12, 21, 14, 18, 27, 
    22, 24, 33, 28, 30, 39, 36, 36, 46, 42, 42, 52, 47, 50, 59, 53, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 
    00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
};