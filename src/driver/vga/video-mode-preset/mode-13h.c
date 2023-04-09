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