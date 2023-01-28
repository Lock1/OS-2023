#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/memory.h"
#include "lib-header/framebuffer.h"

extern void launch_protected_mode(struct GDTDescriptor *gdtdesc);

// GDT
// Null descriptor
// Kernel code
// Kernel data (variables, etc)
struct GlobalDescriptor gdt_records[3] = {
    {0},
    {
     .segment_high = 0xf,
     .segment_low  = 0xffff,
     .base_high    = 0,
     .base_mid     = 0,
     .base_low     = 0,
     .access.non_system = 1,
     .access.type_bit   = 0xA,
     .access.privilege  = 0,
     .access.valid_bit  = 1,
     .opr_32_bit  = 1,
     .long_mode   = 0,
     .granularity = 1,
    },
    {
     .segment_high = 0xf,
     .segment_low  = 0xffff,
     .base_high    = 0,
     .base_mid     = 0,
     .base_low     = 0,
     .access.non_system = 1,
     .access.type_bit   = 0x2,
     .access.privilege  = 0,
     .access.valid_bit  = 1,
     .opr_32_bit  = 1,
     .long_mode   = 0,
     .granularity = 1,
    }
};

struct GDTDescriptor gdtdesc = {
    .address = gdt_records,
    .size    = sizeof(gdt_records),
};

void kernel_setup(void) {
    uint32_t a;
    uint32_t volatile b = 0x0000BABE;
    __asm__("mov $0xCAFE0000, %0" : "=r"(a));
    launch_protected_mode(&gdtdesc);
    framebuffer_write(8, 'H', 10, 15);
    framebuffer_set_cursor(1, 0);
    while (1) b += 1;
}