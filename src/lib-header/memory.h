#ifndef _MEMORY_H
#define _MEMORY_H

#include "lib-header/stdtype.h"

struct GDAccessByte {
    uint8_t type_bit   : 4;
    uint8_t non_system : 1;
    uint8_t privilege  : 2;
    uint8_t valid_bit  : 1;
} __attribute__((packed));

struct GlobalDescriptor {
    // First 32-bit
    uint16_t segment_low;
    uint16_t base_low;

    // Next 16-bit (Bit 32 to 47)
    uint8_t  base_mid;
    struct GDAccessByte access;

    // Next 8-bit (Bit 48 to 55)
    uint8_t segment_high : 4;
    uint8_t _reserved    : 1;
    uint8_t long_mode    : 1;
    uint8_t opr_32_bit   : 1;
    uint8_t granularity  : 1;

    // Last 8-bit (Bit 56 to 63)
    uint8_t base_high;
} __attribute__((packed));

struct GDTDescriptor {
    uint16_t size;
    struct GlobalDescriptor *address;
} __attribute__((packed));

#endif