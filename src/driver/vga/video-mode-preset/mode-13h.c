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