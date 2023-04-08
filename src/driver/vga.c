#include "lib-header/vga.h"
#include "lib-header/portio.h"
#include "lib-header/vga-register.h"

// static struct VGADriverState vga_state = {

// };

static inline uint8_t struct_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

static void vga_set_index_register(struct VGARegisterPort vga_reg, uint8_t index, uint8_t data) {
    out(vga_reg.address_register, index);
    out(vga_reg.data_register, data);
}

void vga_use_graphic_mode(void) {
    // VGA miscellaneous register
    out(_vga_reg_external_output.data_register, struct_serialize(&_vga_reg_mode13h_output));
    out(_vga_reg_external_fc.data_register, struct_serialize(&_vga_reg_mode13h_fc));

    // VGA Indexed register
    vga_set_index_register(_vga_reg_crt_controller, CRT_INDEX_HORIZONTAL_TOTAL, struct_serialize(&_vga_reg_mode13h_horizontal_total));
}