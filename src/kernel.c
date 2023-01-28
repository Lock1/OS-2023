#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/memory.h"
#include "lib-header/framebuffer.h"

extern void launch_protected_mode(void);

struct GlobalDescriptorTable gdt = {
    .entry = {
        {0}, 
        {
            .segment0  = 0xFFFF,
            .segment16 = 0xF,
            .access = {
                .valid           = 1,
                .privilege_level = 0,
                .descriptor_type = 1,
                .type            = 0xA
            },
            .flags = {
                .granularity = 1,
                .opr_size_32 = 1,
                .mode64      = 0
            }
        },
        {
            .access = {
                .privilege_level = 0,
                .type            = 0xA
            }
        },
    }
};

struct GDTDescriptor gdtdesc = {
    .address = &gdt,
    .size    = 256,
};

void kernel_setup(void) {
    uint32_t a;
    uint32_t volatile b = 0x0000BABE;
    __asm__("mov $0xCAFE0000, %0" : "=r"(a));
    load_gdt(gdtdesc);
    launch_protected_mode();
    framebuffer_write(8, 'H', 10, 15);
    framebuffer_set_cursor(1, 0);
    while (1) b += 1;
}