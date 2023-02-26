#include "lib-header/idt.h"

extern void interrupt_handler_8();

struct InterruptDescriptorTable interrupt_descriptor_table = {
    .table = {{0}},
};

struct IDTR _idt_idtr = {
    .address = &interrupt_descriptor_table,
    .size    = IDT_MAX_ENTRY_COUNT,
};

void initialize_idt(void) {
    // Lets test
    set_idt_gate(8, interrupt_handler_8, 0, 0x00);
    // for (uint8_t int_vector = 0; int_vector < 32; int_vector++) {
    // set_idt_gate(int_vector, interrupt_handler_8, 0, 0x00);

    // }
    __asm__ volatile("lidt %0" : : "m"(_idt_idtr));
    __asm__ volatile("sti");
}

void set_idt_gate(uint8_t int_vector, void *handler_address, uint16_t segment, uint8_t privilege) {
    struct InterruptGate *idt_int_gate = &interrupt_descriptor_table.table[int_vector];

    idt_int_gate->offset_low  = 0x0000FFFF  & (uint32_t) handler_address;
    idt_int_gate->offset_high = (0xFFFF0000 & (uint32_t) handler_address) >> 16;
    idt_int_gate->privilege   = 0b11        & privilege;
    idt_int_gate->segment     = segment;

    // Target system 32-bit and flag this as valid interrupt gate
    idt_int_gate->_r_bit_1    = INTERRUPT_GATE_R_BIT_1;
    idt_int_gate->_r_bit_2    = INTERRUPT_GATE_R_BIT_2;
    idt_int_gate->_r_bit_3    = INTERRUPT_GATE_R_BIT_3;
    idt_int_gate->gate_32     = 1;
    idt_int_gate->valid_bit   = 1;
}