#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/memory.h"
#include "lib-header/framebuffer.h"


void kernel_setup(void) {
    uint32_t a;
    uint32_t volatile b = 0x0000BABE;
    __asm__("mov $0xCAFE0000, %0" : "=r"(a));
    framebuffer_write(8, 'H', 10, 15);
    framebuffer_set_cursor(1, 0);
    while (1) b += 1;
}