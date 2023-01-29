#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/memory.h"
#include "lib-header/framebuffer.h"
#include "lib-header/kernel_loader.h"

void kernel_setup(void) {
    uint32_t a;
    uint32_t volatile b = 0x0000BABE;
    __asm__("mov $0xCAFE0000, %0" : "=r"(a));
    launch_protected_mode(&_memory_gdt_descriptor);
    framebuffer_clear();
    for (int i = 0; i < 80; i++) {
        framebuffer_write(0, i, '0' + (i % 10), 0x1 + (i / 10), 0x0);
        if (i < 25)
            framebuffer_write(i, 0, '0' + (i % 10), 0x1 + (i / 10), 0x0);
    }
    framebuffer_write(3, 8, 'H', 10, 15);
    framebuffer_set_cursor(1, 0);
    while (1) b += 1;
}