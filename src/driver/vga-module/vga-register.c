#include "lib-header/driver/vga-module/vga-register.h"

// VGA Register port - Indexed register
const struct VGARegisterPort _vga_reg_sequencer = {
    .address_register = 0x3C4,
    .data_register    = 0x3C5,
};

// Mono use 0x3B4-0x3B5 instead
const struct VGARegisterPort _vga_reg_crt_controller = {
    .address_register = 0x3D4,
    .data_register    = 0x3D5,
};


// VGA Register port - External registers
const struct VGARegisterPort _vga_reg_external_output = {
    .data_register    = 0x3C2,
};

// Assuming color mode is used, for mono use 0x3BA
const struct VGARegisterPort _vga_reg_external_fc = {
    .data_register    = 0x3DA,
};



// Video Mode 13h register values
const struct VGASequencerResetData _vga_reg_mode13h_reset = {
    .asynchronous_reset = 1,
    .synchronous_reset  = 1,
};

const struct VGASequencerClockingModeData _vga_reg_mode13h_clocking_mode = {
    .dot_9_8_mode    = 1,
    .shift_load_rate = 0,
    .dot_clock_rate  = 0,
    .shift_four_mode = 0,
    .screen_disable  = 0,
};

const struct VGASequencerMapMaskData _vga_reg_mode13h_map_mask = {
    .enable_memory_plane_0 = 0,
    .enable_memory_plane_1 = 0,
    .enable_memory_plane_2 = 0,
    .enable_memory_plane_3 = 0,
};

const struct VGASequencerCharacterMapData _vga_reg_mode13h_character_map = {
    .character_set_b      = 0,
    .character_set_a      = 0,
    .second_bit_charset_b = 0,
    .second_bit_charset_a = 0,
};

const struct VGASequencerMemoryModeData _vga_reg_mode13h_sequencer_memory_mode = {
    .extended_memory         = 1,
    .disable_odd_even_memory = 1,
    .enable_chain_four       = 1,
};


// FIXME : CRT Controller
const struct VGACRTControllerHorizontalTotalData _vga_reg_mode13h_horizontal_total = {
    .horizontal_total = 3,
};

const struct VGACRTControllerEndHorizontalDisplayData _vga_reg_mode13h_end_horizontal_display = {
    .end_horizontal_display = 0,
};

const struct VGACRTControllerStartHorizontalBlankingData _vga_reg_mode13h_start_horizontal_blanking = {
    .start_horizontal_blanking = 3,
};

const struct VGACRTControllerEndHorizontalBlankingData _vga_reg_mode13h_end_horizontal_blanking = {
    .end_horizontal_blanking = 0,
    .display_enable_skew     = 0,
    .vertical_rectrace       = 0,
};

const struct VGAExternalOutputRegisterData _vga_reg_mode13h_output = {
    .ioas             = 1,
    .ram_enable       = 1,
    .clock_select     = 0,
    .odd_even_page    = 1,
    .horizontal_sync  = 1,
    .vertical_sync    = 0,
};

const struct VGAExternalFeatureControlData _vga_reg_mode13h_fc = {
    .feature_control0 = 0,
    .feature_control1 = 0,
};