#ifndef _USER_ISR_H
#define _USER_ISR_H

#include "interrupt.h"
#include "stdtype.h"

#define KEYBOARD_DATA_PORT     0x60
#define EXTENDED_SCANCODE_BYTE 0xE0
// QEMU use set 1

void keyboard_isr(void);

#endif