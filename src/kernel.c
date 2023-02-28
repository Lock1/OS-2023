#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/gdt.h"
#include "lib-header/framebuffer.h"
#include "lib-header/kernel_loader.h"
#include "lib-header/idt.h"
#include "lib-header/interrupt.h"
#include "lib-header/keyboard.h"
#include "lib-header/disk.h"

void kernel_setup(void) {
    enter_protected_mode(&_gdt_gdtr);
    pic_remap();
    initialize_idt();
    activate_keyboard_interrupt();
    framebuffer_clear();
    framebuffer_set_cursor(0, 0);

    uint8_t test[512] = {0};
    // for (int i = 0; i < 512; i++)
    //     test[i] = i;

    // write_sectors(test, 11, 1);

    // ITS WORKKKK
    read_sectors(test, 12, 1);

    keyboard_state_activate();
    while (is_keyboard_blocking());


    while (TRUE);
}