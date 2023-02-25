#include "lib-header/idt.h"

#define INTERRUPT_GATE_R_BIT_1 0b000
#define INTERRUPT_GATE_R_BIT_2 0b110
#define INTERRUPT_GATE_R_BIT_3 0b0

void initInterruptGate(struct InterruptGate *ig, uint32_t offset, uint8_t segment, uint8_t privilege) {
    ig->offset_low  = 0x0000FFFF & offset;
    ig->offset_high = (0xFFFF0000 & offset) >> 16;
    ig->privilege   = 0b11       & privilege;
    ig->segment     = segment;

    // Target system 32-bit and flag this as valid interrupt gate
    ig->_r_bit_1    = INTERRUPT_GATE_R_BIT_1;
    ig->_r_bit_2    = INTERRUPT_GATE_R_BIT_2;
    ig->_r_bit_3    = INTERRUPT_GATE_R_BIT_3;
    ig->gate_32     = 1;
    ig->valid_bit   = 1;
}