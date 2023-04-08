#include "lib-header/vga.h"
#include "lib-header/portio.h"
#include "lib-header/vga-register.h"

// static struct VGADriverState vga_state = {

// };

static uint8_t struct_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

void vga_use_graphic_mode(void) {
    out(misc_output_register.data_register, struct_serialize(&misc_mode13h));

}