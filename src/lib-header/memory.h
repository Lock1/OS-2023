#ifndef _MEMORY_H
#define _MEMORY_H

#include "lib-header/stdtype.h"

// FIXME : Improper GDT load

struct SegmentAccess {
    uint8_t type            : 4;
    uint8_t descriptor_type : 1;
    uint8_t privilege_level : 2;
    uint8_t valid           : 1;
} __attribute__((packed));

struct SegmentFlags {
    uint8_t _reserved   : 1;
    uint8_t mode64      : 1;
    uint8_t opr_size_32 : 1;
    uint8_t granularity : 1;
} __attribute__((packed));

struct SegmentDescriptor {
    uint16_t segment0;
    uint16_t base0;
    uint8_t  base16;
    struct SegmentAccess access;
    uint8_t  segment16 : 4;
    struct SegmentFlags  flags;
    uint8_t  base24;
} __attribute__((packed));

struct GlobalDescriptorTable {
    struct SegmentDescriptor entry[32];
} __attribute__((packed));

struct GDTDescriptor {
    struct GlobalDescriptorTable *address;
    uint16_t size;
} __attribute__((packed));

void load_gdt(struct GDTDescriptor gdtdesc);

#endif