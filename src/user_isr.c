#include "lib-header/user_isr.h"
#include "lib-header/portio.h"

uint8_t get_keyboard_scancode(void) {
    return in(KEYBOARD_DATA_PORT);
}

void keyboard_isr(void) {
    uint8_t first_sc = get_keyboard_scancode();
    if (first_sc == EXTENDED_SCANCODE_BYTE) {
        uint8_t extended_sc = get_keyboard_scancode();
    }
    pic_ack(IRQ_KEYBOARD);
}