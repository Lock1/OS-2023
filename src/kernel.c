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

    // TODO : Lets try identify qemu img first
    // and after that we will try to fix outw
    // or try -hda
    // write_sectors(test, 1, 1);

    // ITS WORKKKK
    read_sectors(test, 1, 1);
    // TODO : out16
    // makefile run update

    keyboard_state_activate();
    while (is_keyboard_blocking());


    while (TRUE);
}