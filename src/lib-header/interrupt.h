#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "stdtype.h"

#define PIC1_OFFSET     0x20
#define PIC2_OFFSET     0x28

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)

#define PIC_ACK         0x20

#define ICW1_ICW4       0x01   /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02   /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04   /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08   /* Level triggered (edge) mode */
#define ICW1_INIT       0x10   /* Initialization - required! */

#define ICW4_8086       0x01   /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02   /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08   /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C   /* Buffered mode/master */
#define ICW4_SFNM       0x10   /* Special fully nested (not) */

// PICs IRQ list
#define IRQ_TIMER       0
#define IRQ_KEYBOARD    1



struct CPURegister {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebp;
    uint32_t esp;
} __attribute__((packed));

// Predefined struct by CPU
// Kernel-stack interrupt data
struct InterruptInfo {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

void main_interrupt_handler(struct CPURegister cpu, uint32_t int_number, struct InterruptInfo info);

void activate_keyboard_interrupt(void);

// 1-4 microsecond wait
void io_wait(void);

// Send ACK to PIC
void pic_ack(uint8_t irq);

// Shift PIC interrupt number to 0x20 and 0x28 (master and slave)
void pic_remap(void);

#endif