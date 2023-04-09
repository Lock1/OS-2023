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
        .asynchronous_reset = 1,
        .synchronous_reset  = 1,
    },
    .clocking_mode = {
        .dot_9_8_mode    = 1,
        .shift_load_rate = 0,
        .dot_clock_rate  = 0,
        .shift_four_mode = 0,
        .screen_disable  = 0,
    },
    .map_mask = {
        .enable_memory_plane_0 = 1,
        .enable_memory_plane_1 = 1,
        .enable_memory_plane_2 = 1,
        .enable_memory_plane_3 = 1,
    },
    .character_map = {
        .character_set_b      = 0,
        .character_set_a      = 0,
        .second_bit_charset_b = 0,
        .second_bit_charset_a = 0,
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