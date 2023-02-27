#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/gdt.h"
#include "lib-header/framebuffer.h"
#include "lib-header/kernel_loader.h"
#include "lib-header/idt.h"
#include "lib-header/interrupt.h"


void kernel_setup(void) {
    enter_protected_mode(&_gdt_gdtr);
    initialize_idt();
    pic_remap();
    framebuffer_clear();
    // __asm__("int $0x21");
    out(0x21, 0xfd);
    out(0xa1, 0xff);
    framebuffer_write(3, 8, 'H', 0, 0xF);
    framebuffer_write(3, 9, 'a', 0, 0xF);
    framebuffer_write(3, 10, 'i', 0, 0xF);
    framebuffer_write(3, 11, '!', 0, 0xF);
    framebuffer_set_cursor(3, 10);

    // FIXME : GP fault with error code 0x102?
    // It seems 0x102 mean, IDT on index 32 is fault. For now, yes, but after testing with 33, it is still error
    // Ah crap, its IRQ that shifted to 0x20
    // It is, very high chance that this is IRQ0 timer that hit on PIC1 0 offset
    // as when i move from 0x20 to 0x28, it do fire GPF on 0x142 => index 40
    // GPF trick : rightmost hex = table & external, and left over, multiply by 2 for index

    // TODO : Lets fix IRQ0 timer and set handler
    // TODO : After that we can try to setup keyboard
    // TODO : And FS
    // Lets int 0x20 ourself
    while (1);
}