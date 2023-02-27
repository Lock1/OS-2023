#include "lib-header/keyboard.h"
#include "lib-header/portio.h"
#include "lib-header/framebuffer.h"

static bool    read_extended_mode   = FALSE;
static bool    keyboard_input_on    = FALSE;
static char    keyboard_buffer[256] = {0};
static uint8_t buffer_index         = 0;

const char keyboard_scancode_1_to_ascii_map[256] = {
      0, 0x1B, '1', '2', '3', '4', '5', '6',  '7', '8', '9',  '0',  '-', '=', '\b', '\t',
    'q',  'w', 'e', 'r', 't', 'y', 'u', 'i',  'o', 'p', '[',  ']', '\n',   0,  'a',  's',
    'd',  'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0, '\\',  'z', 'x',  'c',  'v',
    'b',  'n', 'm', ',', '.', '/',   0, '*',    0, ' ',   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0, '-',    0,    0,   0,  '+',    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,

      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
      0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,    0,    0,   0,    0,    0,
};

bool printable_scancode(uint8_t scancode) {
    return scancode != EXTENDED_SCANCODE_BYTE 
      && scancode != EXT_SCANCODE_UP    
      && scancode != EXT_SCANCODE_DOWN  
      && scancode != EXT_SCANCODE_LEFT  
      && scancode != EXT_SCANCODE_RIGHT
      && 32 <= keyboard_scancode_1_to_ascii_map[scancode];
}

uint8_t get_keyboard_scancode(void) {
    return in(KEYBOARD_DATA_PORT);
}

void keyboard_state_activate(void) {
    keyboard_input_on = TRUE;
}

void keyboard_state_deactivate(void) {
    keyboard_input_on = FALSE;
}

void keyboard_isr(void) {
    if (!keyboard_input_on)
        buffer_index = 0;
    else {
        uint8_t  scancode    = get_keyboard_scancode();
        char     mapped_char = keyboard_scancode_1_to_ascii_map[scancode];
        uint16_t position    = framebuffer_get_cursor();
        uint16_t row         = position / 80;
        uint16_t column      = position % 80;
        if (read_extended_mode) {
            switch (scancode) {
                case EXT_SCANCODE_LEFT:
                    framebuffer_set_cursor(row, column - 1);
                    buffer_index--;
                    break;
                case EXT_SCANCODE_RIGHT:
                    framebuffer_set_cursor(row, column + 1);
                    buffer_index++;
                    break;
            }
            read_extended_mode = FALSE;
        } else if (scancode == EXTENDED_SCANCODE_BYTE) {
            read_extended_mode = TRUE;
        } else if (printable_scancode(scancode)) {
            framebuffer_write(row, column, mapped_char, 0xF, 0);
            framebuffer_set_cursor(row, column + 1);
            keyboard_buffer[buffer_index++] = mapped_char;
        } else if (mapped_char == '\n') {
            framebuffer_set_cursor(row + 1, 0);
            keyboard_state_deactivate();
        } else if (mapped_char == '\b') {
            framebuffer_set_cursor(row, column - 1);
            framebuffer_write(row, column - 1, ' ', 0xF, 0);
            keyboard_buffer[buffer_index--] = 0;
        }
    }

    pic_ack(IRQ_KEYBOARD);
}