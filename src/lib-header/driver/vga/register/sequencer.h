#ifndef _VGA_SEQUENCER_REGISTER_H
#define _VGA_SEQUENCER_REGISTER_H

#include <stdint.h>
#include <stdbool.h>
#include "lib-header/driver/vga/vga-register-programmer.h"


// Constant & indices
#define SEQUENCER_REGISTER_COUNT      5

#define SEQUENCER_INDEX_RESET         0
#define SEQUENCER_INDEX_CLOCKING_MODE 1
#define SEQUENCER_INDEX_MAP_MASK      2
#define SEQUENCER_INDEX_CHARACTER_MAP 3
#define SEQUENCER_INDEX_MEMORY_MODE   4



// Register data
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

struct VGASequencerRegister {
    struct VGASequencerResetData        reset;
    struct VGASequencerClockingModeData clocking_mode;
    struct VGASequencerMapMaskData      map_mask;
    struct VGASequencerCharacterMapData character_map;
    struct VGASequencerMemoryModeData   sequencer_memory_mode;
} __attribute__((packed));



extern const struct VGARegisterPort _vga_reg_port_sequencer;



void vga_set_sequencer_register(const struct VGASequencerRegister *sequencer);

#endif