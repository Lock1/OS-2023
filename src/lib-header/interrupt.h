#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "stdtype.h"

struct CPURegister {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebp;
    uint32_t esp;
} __attribute__((packed));

// Predefined struct by CPU
struct InterruptInfo {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

void interrupt_handler(struct CPURegister cpu, uint32_t int_number, struct InterruptInfo info);

#endif