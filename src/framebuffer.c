#include "lib-header/framebuffer.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/portio.h"

enum cursor_command {
    UpperByte = 14u,
    LowerByte = 15u,
};

void framebuffer_set_cursor(uint8_t r, uint8_t c) {
    uint16_t location = r * 0x50 + c;
    out(CURSOR_PORT_CMD, UpperByte);
    out(CURSOR_PORT_DATA, location & 0xFF00u);
    out(CURSOR_PORT_CMD, LowerByte);
    out(CURSOR_PORT_DATA, location & 0x00FFu);
}

void framebuffer_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg) {
    uint8_t  back_color = (bg & 0xF) << 4;
    uint8_t  char_color = (fg & 0xF);
    uint16_t offset     = 2*(80*row + col);
    memset(MEMORY_FRAMEBUFFER + offset, c, 1);
    memset(MEMORY_FRAMEBUFFER + offset + 1, back_color | char_color, 1);
}