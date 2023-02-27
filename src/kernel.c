#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/gdt.h"
#include "lib-header/framebuffer.h"
#include "lib-header/kernel_loader.h"
#include "lib-header/idt.h"
#include "lib-header/interrupt.h"

// extern int interrupt_handler_8(void);

void kernel_setup(void) {
    enter_protected_mode(&_gdt_gdtr);
    initialize_idt();
    pic_remap();
    framebuffer_clear();
    __asm__("int $0x2");
    framebuffer_write(3, 8, 'H', 0, 0xF);
    framebuffer_write(3, 9, 'a', 0, 0xF);
    framebuffer_write(3, 10, 'i', 0, 0xF);
    framebuffer_write(3, 11, '!', 0, 0xF);
    framebuffer_set_cursor(3, 10);

    // FIXME : GP fault with error code 0x102?
    while (1);
}