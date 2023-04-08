#include "lib-header/vga.h"
#include "lib-header/portio.h"
#include "lib-header/vga-register.h"

// static struct VGADriverState vga_state = {

// };

static inline uint8_t struct_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

void vga_use_graphic_mode(void) {
    // VGA miscellaneous register
    out(_vga_reg_external_output.data_register, struct_serialize(&_vga_reg_mode13h_misc));
    out(_vga_reg_external_fc.data_register, struct_serialize(&_vga_reg_mode13h_fc));

    // VGA Indexed register

}