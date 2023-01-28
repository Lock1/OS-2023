#include "lib-header/stdtype.h"
#include "lib-header/memory.h"

void load_gdt(struct GDTDescriptor *gdtdesc) {
    __asm__ volatile(
        "lgdt %0"
        : // <Empty output operand>
        : "m"(gdtdesc)
    );
}