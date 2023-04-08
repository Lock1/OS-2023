#include "lib-header/cpu/portio.h"
#include "lib-header/driver/framebuffer.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"

enum cursor_command {
    UpperByte = 14u,
    LowerByte = 15u,
};

void framebuffer_set_cursor(uint8_t r, uint8_t c) {
    uint16_t location = (r * 0x50 + c) % FRAMEBUFFER_RESOLUTION;
    out(CURSOR_PORT_CMD, UpperByte);
    out(CURSOR_PORT_DATA, (location & 0xFF00u) >> 8);
    out(CURSOR_PORT_CMD, LowerByte);
    out(CURSOR_PORT_DATA, location & 0x00FFu);
}

uint16_t framebuffer_get_cursor(void) {
    uint16_t position = 0;
    out(CURSOR_PORT_CMD, LowerByte);
    position |= in(CURSOR_PORT_DATA);
    out(CURSOR_PORT_CMD, UpperByte);
    position |= ((uint16_t) in(CURSOR_PORT_DATA)) << 8;
    return position;
}

void framebuffer_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg) {
    uint8_t  back_color = (bg & 0xF) << 4;
    uint8_t  char_color = (fg & 0xF);
    uint16_t offset     = 2*(80*row + col);
    memset(MEMORY_FRAMEBUFFER + offset, c, 1);
    memset(MEMORY_FRAMEBUFFER + offset + 1, back_color | char_color, 1);
}

void framebuffer_clear(void) {
    for (size_t i = 0; i < 80; i++) {
        for (size_t j = 0; j < 25; j++) {
            memset(MEMORY_FRAMEBUFFER + 2*(i+80*j),      ' ', 1);
            memset(MEMORY_FRAMEBUFFER + 2*(i+80*j) + 1, 0x0F, 1);
        }
    }
}