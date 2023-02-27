#include "lib-header/user_isr.h"
#include "lib-header/portio.h"
#include "lib-header/framebuffer.h"

#define EXT_SCANCODE_UP    0x48
#define EXT_SCANCODE_DOWN  0x50
#define EXT_SCANCODE_LEFT  0x4B
#define EXT_SCANCODE_RIGHT 0x4D

static uint8_t scancode_buffer[8] = {0};
static bool    read_extended_mode = FALSE;
static bool    keyboard_input_on  = FALSE;

const char keyboard_scancode_1_to_ascii_map[128] = {
      0, 0x1B, '1', '2', '3', '4', '5', '6',  '7', '8', '9',  '0',  '-', '=', '\b', '\t',
    'q',  'w', 'e', 'r', 't', 'y', 'u', 'i',  'o', 'p', '[',  ']', '\n',   0,  'a',  's',
    'd',  'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0, '\\',  'z', 'x',  'c',  'v',
    'b',  'n', 'm', ',', '.', '/',   0, '*',    0, ' ',   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0, '-',    0,    0,   0,  '+',    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
};

bool printable_scancode(uint8_t scancode){
    return scancode != EXTENDED_SCANCODE_BYTE 
      && scancode != EXT_SCANCODE_UP    
      && scancode != EXT_SCANCODE_DOWN  
      && scancode != EXT_SCANCODE_LEFT  
      && scancode != EXT_SCANCODE_RIGHT
      && keyboard_scancode_1_to_ascii_map[scancode] <= 127
      && 32 <= keyboard_scancode_1_to_ascii_map[scancode];
}

uint8_t get_keyboard_scancode(void)
{
    return in(KEYBOARD_DATA_PORT);
}

void state_keyboard_activate(void) {
    keyboard_input_on = TRUE;
}

void state_keyboard_deactivate(void) {
    keyboard_input_on = FALSE;
}

void keyboard_isr(void) {
    if (keyboard_input_on) {
        uint8_t  scancode = get_keyboard_scancode();
        uint16_t position = framebuffer_get_cursor();
        uint16_t row      = position / 80;
        uint16_t column   = position % 80;
        if (read_extended_mode) {
            switch (scancode) {
                case EXT_SCANCODE_UP:
                    framebuffer_set_cursor(row - 1, column);
                    break;
                case EXT_SCANCODE_DOWN:
                    framebuffer_set_cursor(row + 1, column);
                    break;
                case EXT_SCANCODE_LEFT:
                    framebuffer_set_cursor(row, column - 1);
                    break;
                case EXT_SCANCODE_RIGHT:
                    framebuffer_set_cursor(row, column + 1);
                    break;
            }
            read_extended_mode = FALSE;
        } else if (scancode == EXTENDED_SCANCODE_BYTE) {
            read_extended_mode = TRUE;
        }
        else if (printable_scancode(scancode)) {
            framebuffer_write(row, column, keyboard_scancode_1_to_ascii_map[scancode], 0xF, 0);
        }
    }
    pic_ack(IRQ_KEYBOARD);
}