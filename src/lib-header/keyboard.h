#ifndef _USER_ISR_H
#define _USER_ISR_H

#include "interrupt.h"
#include "stdtype.h"

#define KEYBOARD_DATA_PORT     0x60
#define EXTENDED_SCANCODE_BYTE 0xE0
// QEMU use set 1

extern const char keyboard_scancode_1_to_ascii_map[256];

void keyboard_isr(void);
void state_keyboard_activate(void);
void state_keyboard_deactivate(void);

#endif