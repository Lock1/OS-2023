#include "lib-header/interrupt.h"

// interrupt_handler_n in intsetup is placed on IDT
// and all of them will call this interrupt_handler
// this interrupt_handler will call proper handler for all interrupts
void main_interrupt_handler(struct CPURegister cpu, uint32_t int_number, struct InterruptInfo info) {
    switch (int_number) {

    }

    if (int_number == 3)
        cpu.eax = info.cs;
    info.cs = cpu.edx;

    __asm__ volatile ("cli; hlt");
}