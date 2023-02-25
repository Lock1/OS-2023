#ifndef _IDT_H
#define _IDT_H
// TODO : More comment in doxygen IDT

#include "stdtype.h"

// IDT hard limit, see Intel x86 manual 3a - 6.10 Interrupt Descriptor Table
#define IDT_MAX_ENTRY_COUNT 256

extern struct IDTR _idt_idtr;


/**
 * InterruptGate
 * 
 * @param offset_low  Lower 16-bit offset
 * @param segment     Memory segment
 * @param _reserved   Reserved bit
 * @param r_bit_1     Indicating valid interrupt gate, Valid value r_bit_1 = 0b110000
 * @param gate_32     Is this gate size 32-bit? If not then its 16-bit gate
 * @param r_bit_2     Indicating valid interrupt gate, Valid value r_bit_2 = 0b0
 * @param privilege   Descriptor Privilege Level, behave exactly like GDT DPL
 * @param valid_bit   Indicating whether this gate is valid or not (?)
 * @param offset_high Higher 16-bit offset
 */

struct InterruptGate {
    // First 32-bit (Bit 0 to 31)
    uint16_t offset_low;
    uint16_t segment;

    // Last 32-bit (Bit 32 to 63)
    uint8_t _reserved : 5;
    uint8_t _r_bit_1 : 3;
    uint8_t _r_bit_2 : 3;
    uint8_t gate_32  : 1;
    uint8_t _r_bit_3 : 1;
    uint8_t privilege : 2;
    uint8_t valid_bit : 1;
    uint16_t offset_high;
} __attribute__((packed));

/**
 * Interrupt Descriptor Table
 *
 * @param table 256-entry array of InterruptGate
 */
struct InterruptDescriptorTable {
    struct InterruptGate table[IDT_MAX_ENTRY_COUNT];
} __attribute__((packed));

/**
 * IDTR
 *
 * @param address IDT address, IDT should already defined properly
 */
struct IDTR {
    struct InterruptDescriptorTable *address;
} __attribute__((packed));

void initInterruptGate(struct InterruptGate *ig, uint32_t offset, uint8_t segment, uint8_t privilege);

#endif