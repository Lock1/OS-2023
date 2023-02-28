#ifndef _USER_ISR_H
#define _USER_ISR_H

#include "interrupt.h"
#include "stdtype.h"

#define EXT_SCANCODE_UP    0x48
#define EXT_SCANCODE_DOWN  0x50
#define EXT_SCANCODE_LEFT  0x4B
#define EXT_SCANCODE_RIGHT 0x4D

#define KEYBOARD_DATA_PORT     0x60
#define EXTENDED_SCANCODE_BYTE 0xE0

/**
 * keyboard_scancode_1_to_ascii_map[256]
 *
 * Convert scancode values that correspond to ASCII printables
 * 
 * How to use this array: ascii_char = k[scancode]
 * 
 * By default, QEMU using scancode set 1
 */
extern const char keyboard_scancode_1_to_ascii_map[256];

void keyboard_isr(void);
void keyboard_state_activate(void);
void keyboard_state_deactivate(void);
bool is_keyboard_blocking(void);

#endif