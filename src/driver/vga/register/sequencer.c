#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/vga-register.h"

// VGA Register port - Indexed register
const struct VGARegisterPort _vga_reg_port_sequencer = {
    .address_register = 0x3C4,
    .data_register    = 0x3C5,
};



void vga_set_sequencer_register(const struct VGASequencerRegister *sequencer) {
    uint8_t sequencer_index[SEQUENCER_REGISTER_COUNT] = {
        SEQUENCER_INDEX_RESET,
        SEQUENCER_INDEX_CLOCKING_MODE,
        SEQUENCER_INDEX_MAP_MASK,
        SEQUENCER_INDEX_CHARACTER_MAP,
        SEQUENCER_INDEX_MEMORY_MODE,
    };
    uint8_t sequencer_data[SEQUENCER_REGISTER_COUNT] = {
        register_const_serialize(&sequencer->reset),
        register_const_serialize(&sequencer->clocking_mode),
        register_const_serialize(&sequencer->map_mask),
        register_const_serialize(&sequencer->character_map),
        register_const_serialize(&sequencer->sequencer_memory_mode),
    };
    set_indexed_register(_vga_reg_port_sequencer, sequencer_index, sequencer_data, SEQUENCER_REGISTER_COUNT);
}