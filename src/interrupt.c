#include "lib-header/interrupt.h"
#include "lib-header/portio.h"
#include "lib-header/user_isr.h"


// interrupt_handler_n in intsetup is placed on IDT
// and all of them will call this interrupt_handler
// this interrupt_handler will call proper handler for all interrupts
void main_interrupt_handler(struct CPURegister cpu, uint32_t int_number, struct InterruptInfo info) {
    switch (int_number) {
        case PIC1_OFFSET + IRQ_KEYBOARD:
            keyboard_isr();
            break;
    }
}

void io_wait(void) {
    out(0x80, 0);
}

void pic_ack(uint8_t irq) {
    if (irq >= 8)
        out(PIC2_COMMAND, PIC_ACK);
    out(PIC1_COMMAND, PIC_ACK);
}

void pic_remap(void) {
    uint8_t a1, a2;

    // Save masks
    a1 = in(PIC1_DATA); 
    a2 = in(PIC2_DATA);

    // Starts the initialization sequence in cascade mode
    out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); 
    io_wait();
    out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    out(PIC1_DATA, PIC1_OFFSET); // ICW2: Master PIC vector offset
    io_wait();
    out(PIC2_DATA, PIC2_OFFSET); // ICW2: Slave PIC vector offset
    io_wait();
    out(PIC1_DATA, 0b0100);      // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    out(PIC2_DATA, 0b0010);      // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    out(PIC1_DATA, ICW4_8086);
    io_wait();
    out(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore masks
    out(PIC1_DATA, a1);
    out(PIC2_DATA, a2);
}