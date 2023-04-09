#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Indexed register
const struct VGARegisterPort _vga_reg_port_sequencer = {
    .address_register = 0x3C4,
    .data_register    = 0x3C5,
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

void vga_set_sequencer_register(void) {
    uint8_t sequencer_index[5] = {
        SEQUENCER_INDEX_RESET,
        SEQUENCER_INDEX_CLOCKING_MODE,
        SEQUENCER_INDEX_MAP_MASK,
        SEQUENCER_INDEX_CHARACTER_MAP,
        SEQUENCER_INDEX_MEMORY_MODE,
    };
    uint8_t sequencer_data[5] = {
        register_const_serialize(&_vga_reg_mode13h_reset),
        register_const_serialize(&_vga_reg_mode13h_clocking_mode),
        register_const_serialize(&_vga_reg_mode13h_map_mask),
        register_const_serialize(&_vga_reg_mode13h_character_map),
        register_const_serialize(&_vga_reg_mode13h_sequencer_memory_mode),
    };
    set_indexed_register(_vga_reg_port_sequencer, sequencer_index, sequencer_data, 5);
}