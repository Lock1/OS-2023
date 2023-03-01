#ifndef _GDT_H
#define _GDT_H

#include "lib-header/stdtype.h"

#define GDT_MAX_ENTRY_COUNT              32
// As kernel SegmentDescriptor for code located at index 1 in GDT, then segment selector is sizeof(SegmentDescriptor) * 1 = 0x8
#define GDT_KERNEL_CODE_SEGMENT_SELECTOR 0x8
#define GDT_KERNEL_DATA_SEGMENT_SELECTOR 0x10


extern struct GDTR _gdt_gdtr;





/**
 * Segment Descriptor access byte
 * 
 * @param type_bit   4-bit carrying R/W/X, direction, and accessed flag
 * @param non_system 1-bit descriptor type bit, 0 for system segment and 1 for code/data segment (inc. kernel)
 * @param privilege  2-bit privilege level field, PL0 = Maximum, PL3 = User / minimum privilege
 * @param valid_bit  1-bit indicating whether segment is valid
 */
struct SDAccessByte {
    uint8_t type_bit   : 4;
    uint8_t non_system : 1;
    uint8_t privilege  : 2;
    uint8_t valid_bit  : 1;
} __attribute__((packed));

/**
 * Segment Descriptor storing system segment information.
 * Struct defined exactly as Intel Manual Segment Descriptor definition (Figure 3-8 Segment Descriptor).
 * Manual can be downloaded at www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html/ 
 *
 * @param segment_low  16-bit lower-bit segment limit
 * @param base_low     16-bit lower-bit base address
 * @param base_mid     8-bit middle-bit base address
 * @param access       8-bit GDAccessByte structure, contain access flags
 * @param segment_high 4-bit upper-bit segment limit
 * @param _reserved    1-bit unused / reserved for future
 * @param long_mode    1-bit flag indicate 64-bit code segment
 * @param opr_32_bit   1-bit indicating using 32-bit or 16-bit operand mode
 * @param granularity  1-bit whether using block granularity (if 1) or byte-level
 * @param base_high    8-bit upper-bit base address
 */
struct SegmentDescriptor {
    // First 32-bit
    uint16_t segment_low;
    uint16_t base_low;

    // Next 16-bit (Bit 32 to 47)
    uint8_t             base_mid;
    struct SDAccessByte access;

    // Next 8-bit (Bit 48 to 55)
    uint8_t segment_high : 4;
    uint8_t _reserved    : 1;
    uint8_t long_mode    : 1;
    uint8_t opr_32_bit   : 1;
    uint8_t granularity  : 1;

    // Last 8-bit (Bit 56 to 63)
    uint8_t base_high;
} __attribute__((packed));

/**
 * Global Descriptor Table containing list of segment descriptor. One GDT already defined in gdt.c.
 * More details at https://wiki.osdev.org/GDT_Tutorial
 * 
 * @param table Fixed-width array of SegmentDescriptor with size GDT_MAX_ENTRY_COUNT
 */
struct GlobalDescriptorTable {
    struct SegmentDescriptor table[GDT_MAX_ENTRY_COUNT];
} __attribute__((packed));

/**
 * GDTR, carrying information where's the GDT located and GDT size.
 * Global kernel variable defined at gdt.c.
 * 
 * @param size    Global Descriptor Table size, use sizeof operator
 * @param address GDT address, GDT should already defined properly
 */
struct GDTR {
    uint16_t                     size;
    struct GlobalDescriptorTable *address;
} __attribute__((packed));

#endif