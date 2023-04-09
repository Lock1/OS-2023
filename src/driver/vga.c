#include "lib-header/cpu/portio.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/vga/register/external.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/driver/vga/register/crt-controller.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/attribute-controller.h"

void vga_use_video_mode_13h(void) {
    vga_set_external_register();
    vga_set_sequencer_register();
    vga_set_crt_controller_register();
    vga_set_graphics_register();
    vga_set_attribute_controller_register();
    // TODO : vga_set_mode_13h_ (rename to underscore)

    // TODO : Set palettes
}
