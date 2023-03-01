#ifndef _IDT_H
#define _IDT_H

#include "stdtype.h"

// IDT hard limit, see Intel x86 manual 3a - 6.10 Interrupt Descriptor Table
#define IDT_MAX_ENTRY_COUNT    256
#define INTERRUPT_GATE_R_BIT_1 0b000
#define INTERRUPT_GATE_R_BIT_2 0b110
#define INTERRUPT_GATE_R_BIT_3 0b0

extern struct IDTR _idt_idtr;

/**
 * InterruptGate
 *
 * @param offset_low  Lower 16-bit offset
 * @param segment     Memory segment
 * @param _reserved   Reserved bit
 * @param _r_bit_1    Reserved & predetermined value for valid interrupt gate
 * @param _r_bit_2    Reserved & predetermined value for valid interrupt gate
 * @param gate_32     Is this gate size 32-bit? If not then its 16-bit gate
 * @param _r_bit_3    Reserved & predetermined value for valid interrupt gate
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
    uint16_t                         size;
    struct InterruptDescriptorTable *address;
} __attribute__((packed));

void set_idt_gate(uint8_t int_vector, void *handler_address, uint16_t gdt_seg_selector, uint8_t privilege);

void initialize_idt(void);

#endif