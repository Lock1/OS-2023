#include "lib-header/cpu/portio.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/vga-module/vga-register.h"

static inline uint8_t struct_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

static void vga_set_index_register(struct VGARegisterPort vga_reg, uint8_t index, uint8_t data) {
    out(vga_reg.address_register, index);
    out(vga_reg.data_register, data);
}

static void set_external_misc_register(void) {
    out(_vga_reg_external_output.data_register, struct_serialize(&_vga_reg_mode13h_output));
    out(_vga_reg_external_fc.data_register, struct_serialize(&_vga_reg_mode13h_fc));
}

static void set_indexed_register(struct VGARegisterPort vga_reg, uint8_t *indexes, uint8_t *datas, uint32_t count) {
    for (uint32_t i = 0; i < count; i++)
        vga_set_index_register(vga_reg, indexes[i], datas[i]);
}

static void set_sequencer_register(void) {
    uint8_t sequencer_index[5] = {
        SEQUENCER_INDEX_RESET,
        SEQUENCER_INDEX_CLOCKING_MODE,
        SEQUENCER_INDEX_MAP_MASK,
        SEQUENCER_INDEX_CHARACTER_MAP,
        SEQUENCER_INDEX_MEMORY_MODE,
    };
    uint8_t sequencer_data[5] = {
        struct_serialize(&_vga_reg_mode13h_reset),
        struct_serialize(&_vga_reg_mode13h_clocking_mode),
        struct_serialize(&_vga_reg_mode13h_map_mask),
        struct_serialize(&_vga_reg_mode13h_character_map),
        struct_serialize(&_vga_reg_mode13h_sequencer_memory_mode),
    };
    set_indexed_register(_vga_reg_crt_controller, sequencer_index, sequencer_data, 5);
}

// static void set_crt_controller_register(void) {
//     uint8_t crt_controller_index[4] = {
//         CRT_INDEX_HORIZONTAL_TOTAL,
//         CRT_INDEX_END_HORIZONTAL_DISPLAY,
//         CRT_INDEX_START_HORIZONTAL_BLANKING,
//         CRT_INDEX_END_HORIZONTAL_BLANKING,
//     };
//     uint8_t crt_controller_data[4] = {
//         struct_serialize(&_vga_reg_mode13h_horizontal_total),
//         struct_serialize(&_vga_reg_mode13h_end_horizontal_display),
//         struct_serialize(&_vga_reg_mode13h_start_horizontal_blanking),
//         struct_serialize(&_vga_reg_mode13h_end_horizontal_blanking),
//     };
//     set_indexed_register(_vga_reg_crt_controller, crt_controller_index, crt_controller_data, 4);
// }


void vga_use_graphic_mode(void) {
    set_external_misc_register();
    set_sequencer_register();
    // set_crt_controller_register();
}
