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