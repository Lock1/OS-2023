#include "lib-header/cpu/portio.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/sequencer.h"

void vga_use_graphic_mode(void) {
    vga_set_external_register();
    vga_set_sequencer_register();
    // vga_set_crt_controller_register();
}
