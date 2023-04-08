#include "lib-header/vga.h"
#include "lib-header/portio.h"
#include "lib-header/vga-register.h"

// static struct VGADriverState vga_state = {

// };

static inline uint8_t struct_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

void vga_use_graphic_mode(void) {
    out(_vga_reg_misc_output_register.data_register, struct_serialize(&_vga_reg_mode13h_misc));

}